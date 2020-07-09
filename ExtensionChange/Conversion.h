#pragma once
#include <string>

class Conversion
{
private:

	const CString m_PreviousExtension;
	const CString m_AfterExtension;

public:

	Conversion(CString previous_extension,CString after_extension);

	CString ConvertExtensionString(CString Filepath);
	void RenameExtension(CString Filepath);
};