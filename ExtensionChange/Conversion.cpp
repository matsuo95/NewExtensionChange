#include "pch.h"
#include "Conversion.h"

Conversion::Conversion(CString previousExtension, CString afterExtension)
	:m_previousExtension(previousExtension),m_afterExtension(afterExtension)
{
};

CString Conversion::ConvertExtensionString(CString filePath) { // 文字列の変更のみ

	CString fileName = filePath.Right(_tcslen(filePath) - filePath.ReverseFind(L'\\') - 1);
	CString fileExtension = filePath.Right(_tcslen(filePath) - filePath.ReverseFind(L'.') - 1);

	if (m_previousExtension == L"" && fileName.ReverseFind(L'.') == -1) { // 変換前の拡張子が指定されておらず、引数として与えられたファイルにも拡張子がない
		filePath += (L'.' + m_afterExtension);
	}
	else if (fileExtension == m_previousExtension) { // 引数として与えられたファイルの拡張子 == 変換前の拡張子
		filePath.Delete(filePath.ReverseFind(L'.') + 1, _tcslen(m_previousExtension));
		filePath += m_afterExtension;
	}

	return filePath;
}

int Conversion::RenameExtension(CString filePath) {

	CString newFilePath = ConvertExtensionString(filePath);
	int res = _wrename(filePath, newFilePath);

	return res;
}