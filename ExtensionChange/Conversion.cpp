#include "pch.h"
#include "Conversion.h"

Conversion::Conversion(CString previousExtension, CString afterExtension)
	:m_previousExtension(previousExtension),m_afterExtension(afterExtension)
{
};

CString Conversion::ConvertExtensionString(CString filePath) {
	// ï∂éöóÒÇÃïœçXÇÃÇ›

	if (m_previousExtension == L"" && filePath.Find(L'.') == -1) {
		filePath += (L'.' + m_afterExtension);
	}
	else if (filePath.Right(_tcslen(filePath) - filePath.ReverseFind(L'.') - 1) == m_previousExtension) {
		filePath.Replace(m_previousExtension, m_afterExtension);
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