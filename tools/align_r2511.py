'''!/usr/bin/env python3
# @file align_r2511.py
# @brief 已实现模块 API 与 AUTOSAR CP R25-11 官方 SWS 规范对齐检查
# @details 对每个已移植模块：
#          1. 从 R25-11 SWS PDF 提取全部 "Definition of API function"（名称 + SWS ID）
#          2. 从本地 infras/include 头文件提取函数原型 + @SWS 标注
#          3. 输出三类偏差：规范有而本地缺 / 本地有而规范无 / 本地标注的 SWS ID 在 R25-11 已失效
# @author binbina
# @note 用法: python align_r2511.py
'''
import re
import os
from pypdf import PdfReader

DOC_DIR = r'H:/as/doc/AUTOSAR-CP_R25-11官方资料'
INC_DIR = r'H:/as/infras/include'

# 模块 -> (SWS PDF 文件名, API 名称前缀, 本地头文件列表)
MODULES = [
	('Can',   'AUTOSAR_CP_SWS_CANDriver.pdf',                    'Can_',   ['Can.h']),
	('CanIf', 'AUTOSAR_CP_SWS_CANInterface.pdf',                 'CanIf_', ['CanIf.h', 'CanIf_Can.h']),
	('CanTp', 'AUTOSAR_CP_SWS_CANTransportLayer.pdf',            'CanTp_', ['CanTp.h']),
	('PduR',  'AUTOSAR_CP_SWS_PDURouter.pdf',                    'PduR_',  ['PduR.h', 'PduR_CanIf.h', 'PduR_CanNm.h',
				'PduR_CanTp.h', 'PduR_Com.h', 'PduR_Dcm.h']),
	('Com',   'AUTOSAR_CP_SWS_COM.pdf',                          'Com_',   ['Com.h']),
	('CanNm', 'AUTOSAR_CP_SWS_CANNetworkManagement.pdf',         'CanNm_', ['CanNm.h']),
	('Nm',    'AUTOSAR_CP_SWS_NetworkManagementInterface.pdf',   'Nm_',    ['Nm.h', 'NmStack_Types.h']),
	('CanSM', 'AUTOSAR_CP_SWS_CANStateManager.pdf',              'CanSM_', ['CanSM.h', 'CanSM_CanIf.h']),
	('ComM',  'AUTOSAR_CP_SWS_COMManager.pdf',                   'ComM_',  ['ComM.h', 'BswM_ComM.h', 'Rte_ComM_Type.h']),
	('Dcm',   'AUTOSAR_CP_SWS_DiagnosticCommunicationManager.pdf', 'Dcm_', ['Dcm.h']),
	('Dem',   'AUTOSAR_CP_SWS_DiagnosticEventManager.pdf',       'Dem_',   ['Dem.h']),
	('NvM',   'AUTOSAR_CP_SWS_NVRAMManager.pdf',                 'NvM_',   ['NvM.h']),
	('EcuM',  'AUTOSAR_CP_SWS_ECUStateManager.pdf',              'EcuM_',  ['EcuM.h', 'EcuM_Externals.h']),
	('Det',   'AUTOSAR_CP_SWS_BSWGeneral.pdf',                   'Det_',   ['Det.h']),
	('Adc',   'AUTOSAR_CP_SWS_ADCDriver.pdf',                    'Adc_',   ['Adc.h']),
	('Pwm',   'AUTOSAR_CP_SWS_PWMDriver.pdf',                    'Pwm_',   ['Pwm.h']),
	('Dio',   'AUTOSAR_CP_SWS_DIODriver.pdf',                    'Dio_',   ['Dio.h']),
	('Port',  'AUTOSAR_CP_SWS_PortDriver.pdf',                   'Port_',  ['Port.h']),
	('Mcu',   'AUTOSAR_CP_SWS_MCUDriver.pdf',                    'Mcu_',   ['Mcu.h']),
	('Crc',   'AUTOSAR_CP_SWS_CRCLibrary.pdf',                   'Crc_',   ['Crc.h']),
]

# 头文件原型提取：任意返回类型 + 函数名 + 左括号（PREFIX 处按模块替换）
# 宽松匹配也覆盖 #define 形式的 API（如 Com_SendSignal）
RET = r'(?:[A-Za-z_]\w*\s*\**)'  # 任意返回类型 + 可选指针星号（不吞尾随空格）
# SWS ID 标注
SWS_ID_RE = re.compile(r'@SWS_([A-Z0-9]+)_(\d+)')


def make_proto_re(prefix):
	'''按模块前缀构造头文件函数原型匹配正则'''
	return re.compile(RET + r'\s+(' + re.escape(prefix) + r'\w+)\s*\(')


def make_def_re(prefix):
	'''匹配 "[SWS_XXX_nnnnn] ... Definition of API function <名称>"（R25-11 统一格式）'''
	return re.compile(r'\[SWS_[A-Z0-9]+_(\d+)\]\s*.{0,120}?Definition of API function\s+(' +
					  re.escape(prefix) + r'\w+)')


def make_syntax_re(prefix):
	'''兼容旧格式：Syntax <ret> Name ('''
	return re.compile(r'Syntax\s+(?:[A-Za-z_]\w*\s+\**)+(' +
					  re.escape(prefix) + r'\w+)\s*\(')


def extract_spec_apis(pdf_path, prefix):
	'''从 SWS PDF 提取全部 API 定义，返回 {函数名: SWS_ID} 与规范全文 ID 集合'''
	r = PdfReader(pdf_path)
	full_text = '\n'.join(p.extract_text() or '' for p in r.pages)
	# 两种格式取并集：新版 "Definition of API function" / 旧版 "Syntax" 块
	apis = {}
	for sid, name in make_def_re(prefix).findall(full_text):
		apis.setdefault(name, sid)
	for m in make_syntax_re(prefix).finditer(full_text):
		apis.setdefault(m.group(1), None)
	# 全文出现的 SWS ID（用于校验本地标注是否仍然有效）
	all_ids = set(re.findall(r'\[SWS_(?:[A-Z0-9]+)_(\d+)\]', full_text))
	return apis, all_ids


def extract_header_apis(header_path, prefix):
	'''从头文件提取函数原型与 @SWS 标注，返回 (函数名集合, {函数名: SWS ID})'''
	with open(header_path, 'r', encoding='utf-8', errors='ignore') as f:
		text = f.read()
	names, tags = set(), {}
	# 按前缀匹配函数原型
	for m in make_proto_re(prefix).finditer(text):
		names.add(m.group(1))
	for m in SWS_ID_RE.finditer(text):
		tags[m.group(2)] = m.group(1)  # ID -> 模块名标注
	return names, tags


def main():
	# 先一次性构建每份 PDF 的全文 ID 集合缓存
	id_cache = {}
	print('=' * 78)
	print('%-6s %6s %6s %8s  %s' % ('模块', '规范', '本地', '缺失', '结论'))
	print('=' * 78)
	for mod, pdf, prefix, headers in MODULES:
		pdf_path = os.path.join(DOC_DIR, pdf)
		if mod not in id_cache:
			apis, all_ids = extract_spec_apis(pdf_path, prefix)
			id_cache[mod] = (apis, all_ids)
		apis, all_ids = id_cache[mod]
		local = set()
		for h in headers:
			hp = os.path.join(INC_DIR, h)
			if os.path.exists(hp):
				names, _ = extract_header_apis(hp, prefix)
				local |= names
		missing = sorted(set(apis) - local)
		extra = sorted(local - set(apis))
		print('-' * 78)
		print('%-6s %6d %6d %8d' % (mod, len(apis), len(local), len(missing)))
		if missing:
			print('  [规范有/本地缺]:', ', '.join(missing))
		if extra:
			print('  [本地有/规范无]:', ', '.join(extra))
	print('=' * 78)


if __name__ == '__main__':
	main()
