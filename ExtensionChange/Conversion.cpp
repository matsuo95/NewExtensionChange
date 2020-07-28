#include "pch.h"
#include "Conversion.h"

Conversion::Conversion(CString previousExtension, CString afterExtension)
	:m_previousExtension(previousExtension),m_afterExtension(afterExtension)
{
};

CString Conversion::ConvertExtensionString(CString filePath) { // ï∂éöóÒÇÃïœçXÇÃÇ›

	if (m_previousExtension == L"") {
		filePath += (L'.');
	}
	else {
		filePath.Delete(filePath.ReverseFind(L'.') + 1, _tcslen(m_previousExtension));
	}

	filePath += m_afterExtension;

	return filePath;
}

int Conversion::RenameExtension(CString filePath) {

	CString fileName = filePath.Right(_tcslen(filePath) - filePath.ReverseFind(L'\\') - 1);
	CString fileExtension = fileName.Right(_tcslen(fileName) - fileName.ReverseFind(L'.') - 1);

	if (fileExtension == fileName) {
		fileExtension = L"";
	}

	int res = 0;

	if (fileExtension == m_previousExtension) {
		CString newFilePath = ConvertExtensionString(filePath);
		res = _wrename(filePath, newFilePath);
	}

	return res;
}