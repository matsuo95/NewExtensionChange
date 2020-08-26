#include "pch.h"
#include "Conversion.h"

Conversion::Conversion(CString previousExtension, CString afterExtension)
	:m_previousExtension(previousExtension),m_afterExtension(afterExtension)
{
}

CString Conversion::ConvertExtensionString(CString filePath) {//ファイルパスの拡張子部分の文字列変更

	if (m_previousExtension == _T("")) 
	{
		filePath += (_T('.'));
	}
	else
	{
		filePath.Delete(filePath.ReverseFind(_T('.')) + 1, _tcslen(m_previousExtension));
	}

	filePath += m_afterExtension;

	return filePath;
}

int Conversion::RenameExtension(CString filePath) {//_wrename関数でファイルパスを変更

	CString fileName = filePath.Right(_tcslen(filePath) - filePath.ReverseFind(_T('\\')) - 1);

	CString fileExtension = fileName.Right(_tcslen(fileName) - fileName.ReverseFind(_T('.')) - 1);

	if (fileExtension == fileName) 
	{
		fileExtension = _T("");
	}

	int res = 0;

	if (fileExtension == m_previousExtension) 
	{
		CString newFilePath = ConvertExtensionString(filePath);
		res = _trename(filePath, newFilePath);
	}

	return res;
}