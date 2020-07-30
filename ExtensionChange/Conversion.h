#pragma once

class Conversion
{

public:

	Conversion(CString previousExtension, CString afterExtension);

	int RenameExtension(CString filepath);

private:

	const CString m_previousExtension;
	const CString m_afterExtension;

	CString ConvertExtensionString(CString filePath);

};