﻿
// ExtensionChangeDlg.h : ヘッダー ファイル
//

#pragma once

#include <set>

// CExtensionChangeDlg ダイアログ
class CExtensionChangeDlg : public CDialogEx
{
// コンストラクション
public:
	CExtensionChangeDlg(CWnd* pParent = nullptr); // 標準コンストラクター

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_EXTENSIONCHANGE_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX); // DDX/DDV サポート

// 実装
protected:
	HICON m_hIcon;

	// 生成された、メッセージ割り当て関数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon(); 
	DECLARE_MESSAGE_MAP()
public:
	CEdit m_cPreviousExtension;

	CString m_previousExtension;
	CString m_afterExtension;

	CListBox m_convertFilePath;

	std::set<CString> m_setFileList;
	int m_addListboxCount = 0;

	afx_msg void OnBnClickedReferenceFileButton();
	afx_msg void OnBnClickedReferenceFolderButton();
	afx_msg void OnBnClickedConversionFileButton();
	afx_msg void OnBnClickedClearButton();

	afx_msg void OnDropFiles(HDROP hDropInfo);

	BOOL SelectFolder(HWND hWnd, LPTSTR lpSelectPath, UINT nFlag, LPCTSTR lpTitle);
	void FileSearch(CString path);

	void ClearListbox();

	void AddListbox(CString filePath);
};