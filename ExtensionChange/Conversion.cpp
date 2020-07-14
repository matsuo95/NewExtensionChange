#include "pch.h"
#include "Conversion.h"

Conversion::Conversion(CString previousExtension, CString afterExtension)
	:m_previousExtension(previousExtension),m_afterExtension(afterExtension)
{
};

CString Conversion::ConvertExtensionString(CString filePath) { // 文字列の変更のみ

	if (m_previousExtension == L"" && filePath.Find(L'.') == -1) { // 拡張子がないとき
		filePath += (L'.' + m_afterExtension);
	}
	else if (filePath.Right(_tcslen(filePath) - filePath.ReverseFind(L'.') - 1) == m_previousExtension) { // 実際のファイルの拡張子 == 変換前の拡張子
		filePath.Delete(filePath.ReverseFind(L'.') + 1, _tcslen(filePath) - filePath.ReverseFind(L'.') - 1);
		filePath += m_afterExtension;
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