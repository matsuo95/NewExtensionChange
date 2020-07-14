#include "pch.h"
#include "Conversion.h"

Conversion::Conversion(CString previousExtension, CString afterExtension)
	:m_previousExtension(previousExtension),m_afterExtension(afterExtension)
{
};

CString Conversion::ConvertExtensionString(CString filePath) { // ������̕ύX�̂�

	if (m_previousExtension == L"" && filePath.Find(L'.') == -1) { // �ϊ��O�̊g���q���w�肳��Ă��炸�A�����Ƃ��ė^����ꂽ�t�@�C���ɂ��g���q���Ȃ�
		filePath += (L'.' + m_afterExtension);
	}
	else if (filePath.Right(_tcslen(filePath) - filePath.ReverseFind(L'.') - 1) == m_previousExtension) { // �����Ƃ��ė^����ꂽ�t�@�C���̊g���q == �ϊ��O�̊g���q
		filePath.Delete(filePath.ReverseFind(L'.') + 1, _tcslen(m_previousExtension));
		filePath += m_afterExtension;
	}

	return filePath;
}

void Conversion::RenameExtension(CString filePath) {

	std::string oldFilePath = CStringA(filePath).GetBuffer();
	const char* PreviousFilePath = oldFilePath.c_str();

	std::string newFilePath = CStringA(ConvertExtensionString(filePath)).GetBuffer();
	const char* AfterFilePath = newFilePath.c_str();

	rename(PreviousFilePath, AfterFilePath);
}