#include "pch.h"
#include "Conversion.h"

Conversion::Conversion(CString previous_extension, CString after_extension)
	:m_PreviousExtension(previous_extension),m_AfterExtension(after_extension)
{
};

CString Conversion::ConvertExtensionString(CString Filepath) {
	// ï∂éöóÒÇÃïœçXÇÃÇ›
	
	std::string str_PreviousExtension, str_AfterExtension, str_Filepath;
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
	return_Filepath = str_Filepath.c_str();

	return return_Filepath;
}

void Conversion::RenameExtension(CString Filepath) {

	std::string str_Filepath = CStringA(Filepath).GetBuffer();
	const char* previous_filepath = str_Filepath.c_str();

	std::string str_newFilepath = CStringA(ConvertExtensionString(Filepath)).GetBuffer();
	const char* after_filepath = str_newFilepath.c_str();

	rename(previous_filepath, after_filepath);
}