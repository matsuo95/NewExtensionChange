#include "pch.h"
#include "Conversion.h"

Conversion::Conversion(CString previous_extension, CString after_extension)
	:m_PreviousExtension(previous_extension),m_AfterExtension(after_extension)
{
};

CString Conversion::ConvertExtensionString(CString Filepath) {
	// 文字列の変更のみ
	
	string str_PreviousExtension, str_AfterExtension, str_Filepath;
	str_PreviousExtension = CStringA(m_PreviousExtension).GetBuffer();
	str_AfterExtension = CStringA(m_AfterExtension).GetBuffer();
	str_Filepath = CStringA(Filepath).GetBuffer();

	auto pos = str_Filepath.rfind(str_PreviousExtension);
	auto len = str_PreviousExtension.length();

	if (pos != std::string::npos && pos == (str_Filepath.length() - len)) {
		str_Filepath.replace(pos, len, str_AfterExtension);
	}

	CString return_Filepath;
	return_Filepath = str_Filepath.c_str();

	return return_Filepath;
}

void Conversion::RenameExtension(CString Filepath) {

	string str_Filepath = CStringA(Filepath).GetBuffer();
	const char* previous_filepath = str_Filepath.c_str();

	string str_newFilepath = CStringA(ConvertExtensionString(Filepath)).GetBuffer();
	const char* after_filepath = str_newFilepath.c_str();

	rename(previous_filepath, after_filepath);
}