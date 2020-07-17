#pragma once
#include <string>

class Conversion
{
private:

	const CString m_previousExtension;
	const CString m_afterExtension;

	CString ConvertExtensionString(CString filePath);

public:

	Conversion(CString previousExtension,CString afterExtension);

	int RenameExtension(CString filepath);
};