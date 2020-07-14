#pragma once
#include <string>

class Conversion
{
private:

	const CString m_previousExtension;
	const CString m_afterExtension;

public:

	Conversion(CString previousExtension,CString afterExtension);

	CString ConvertExtensionString(CString filePath);
	int RenameExtension(CString filepath);
};