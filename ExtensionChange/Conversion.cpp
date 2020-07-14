#include "pch.h"
#include "Conversion.h"

Conversion::Conversion(CString previousExtension, CString afterExtension)
	:m_previousExtension(previousExtension),m_afterExtension(afterExtension)
{
};

CString Conversion::ConvertExtensionString(CString filePath) {
	// ï∂éöóÒÇÃïœçXÇÃÇ›
	
	/*std::string str_PreviousExtension, str_AfterExtension, str_Filepath;
	str_PreviousExtension = CStringA(m_PreviousExtension).GetBuffer();
	str_AfterExtension = CStringA(m_AfterExtension).GetBuffer();
	str_Filepath = CStringA(Filepath).GetBuffer();

	auto pos = str_Filepath.rfind(str_PreviousExtension);
	auto previous_extension_length = str_PreviousExtension.length();

	if (str_PreviousExtension == "" && str_Filepath.rfind(".") == std::string::npos) {
		str_Filepath.insert(str_Filepath.length(), "." + str_AfterExtension);
	}
	else if (str_PreviousExtension != "" && pos == (str_Filepath.length() - previous_extension_length)) {
		str_Filepath.replace(pos, previous_extension_length, str_AfterExtension);
	}

	CString return_Filepath;
	return_Filepath = str_Filepath.c_str();*/

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