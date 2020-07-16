
// ExtensionChangeDlg.cpp : 実装ファイル
//

#include "pch.h"
#include "framework.h"
#include "ExtensionChange.h"
#include "ExtensionChangeDlg.h"
#include "afxdialogex.h"

#include "Conversion.h"
#include <atlpath.h>


#ifdef _DEBUG
#define new DEBUG_NEW
#endif

// アプリケーションのバージョン情報に使われる CAboutDlg ダイアログ

class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// ダイアログ データ
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV サポート

// 実装
protected:
	DECLARE_MESSAGE_MAP()
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
END_MESSAGE_MAP()


// CExtensionChangeDlg ダイアログ



CExtensionChangeDlg::CExtensionChangeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_EXTENSIONCHANGE_DIALOG, pParent)
	
	, m_text_previousExtension(_T(""))
	, m_text_afterExtension(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CExtensionChangeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_EDIT2, m_edit_previousExtension);
	DDX_Control(pDX, IDC_EDIT3, m_edit_afterExtension);
	DDX_Control(pDX, IDC_LIST1, m_list_filePath);
	DDX_Text(pDX, IDC_EDIT2, m_text_previousExtension);
	DDX_Text(pDX, IDC_EDIT3, m_text_afterExtension);
}

BEGIN_MESSAGE_MAP(CExtensionChangeDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BUTTON4, &CExtensionChangeDlg::OnBnClickedReferenceListButton)
	ON_BN_CLICKED(IDC_BUTTON3, &CExtensionChangeDlg::OnBnClickedConversionListButton)
	ON_BN_CLICKED(IDC_BUTTON5, &CExtensionChangeDlg::OnBnClickedReferenceFolderButton)
	ON_WM_DROPFILES()
	ON_WM_DROPFILES()
	ON_BN_CLICKED(IDC_BUTTON1, &CExtensionChangeDlg::OnBnClickedClearButton)
END_MESSAGE_MAP()


// CExtensionChangeDlg メッセージ ハンドラー

BOOL CExtensionChangeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// "バージョン情報..." メニューをシステム メニューに追加します。

	// IDM_ABOUTBOX は、システム コマンドの範囲内になければなりません。
	ASSERT((IDM_ABOUTBOX & 0xFFF0) == IDM_ABOUTBOX);
	ASSERT(IDM_ABOUTBOX < 0xF000);

	CMenu* pSysMenu = GetSystemMenu(FALSE);
	if (pSysMenu != nullptr)
	{
		BOOL bNameValid;
		CString strAboutMenu;
		bNameValid = strAboutMenu.LoadString(IDS_ABOUTBOX);
		ASSERT(bNameValid);
		if (!strAboutMenu.IsEmpty())
		{
			pSysMenu->AppendMenu(MF_SEPARATOR);
			pSysMenu->AppendMenu(MF_STRING, IDM_ABOUTBOX, strAboutMenu);
		}
	}

	// このダイアログのアイコンを設定します。アプリケーションのメイン ウィンドウがダイアログでない場合、
	//  Framework は、この設定を自動的に行います。
	SetIcon(m_hIcon, TRUE);			// 大きいアイコンの設定
	SetIcon(m_hIcon, FALSE);		// 小さいアイコンの設定

	// TODO: 初期化をここに追加します。

	CString previous_extension_default("116");
	((CEdit*)GetDlgItem(IDC_EDIT2))->SetWindowText(previous_extension_default);

	CString after_extension_default("198");
	((CEdit*)GetDlgItem(IDC_EDIT3))->SetWindowText(after_extension_default);

	DragAcceptFiles();

	return TRUE;  // フォーカスをコントロールに設定した場合を除き、TRUE を返します。
}

void CExtensionChangeDlg::OnSysCommand(UINT nID, LPARAM lParam)
{
	if ((nID & 0xFFF0) == IDM_ABOUTBOX)
	{
		CAboutDlg dlgAbout;
		dlgAbout.DoModal();
	}
	else
	{
		CDialogEx::OnSysCommand(nID, lParam);
	}
}

// ダイアログに最小化ボタンを追加する場合、アイコンを描画するための
//  下のコードが必要です。ドキュメント/ビュー モデルを使う MFC アプリケーションの場合、
//  これは、Framework によって自動的に設定されます。

void CExtensionChangeDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 描画のデバイス コンテキスト

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// クライアントの四角形領域内の中央
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// アイコンの描画
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

// ユーザーが最小化したウィンドウをドラッグしているときに表示するカーソルを取得するために、
//  システムがこの関数を呼び出します。
HCURSOR CExtensionChangeDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}

void CExtensionChangeDlg::OnBnClickedReferenceListButton()
{
	m_edit_previousExtension.GetWindowTextW(m_text_previousExtension);

	CString txt1(" Files (*."), txt2(")|*."), txt3(";||");
	CString filter(m_text_previousExtension + txt1 + m_text_previousExtension + txt2 + m_text_previousExtension + txt3);
	CString         filePath, strBuf;
	POSITION        pos = NULL;
	CFileDialog     selDlg(TRUE, NULL, NULL,OFN_HIDEREADONLY | OFN_ALLOWMULTISELECT, filter);
	int             err = 0, lbErr = 0;

	// ファイル名リスト用メモリ確保
	if (!err)
	{
		try
		{
			selDlg.GetOFN().lpstrFile = strBuf.GetBuffer(MAX_PATH * 100);
			selDlg.GetOFN().nMaxFile = MAX_PATH * 100;
		}
		catch (...) { err = 1; }
	}
	if (!err) if (selDlg.DoModal() != IDOK) err = 1;
	if (!err) if ((pos = selDlg.GetStartPosition()) == NULL) err = 1;
	if (!err)
	{
		while (pos)
		{
			filePath = selDlg.GetNextPathName(pos);

			if (listBox.count(filePath) == 1) {
				err = 1;
			}
			else {
				listBox.insert(filePath);
			}

			if (!err)
			{
				m_list_filePath.AddString(filePath);
			}
			if (err) break;
		}
		UpdateData(TRUE);
	}
	strBuf.ReleaseBuffer();

	return;
}

void CExtensionChangeDlg::OnBnClickedConversionListButton()
{
	int listboxCount = m_list_filePath.GetCount();

	if (listboxCount == 0) {
		AfxMessageBox(_T("変換するファイルがありません"));
		return;
	}

	CString filePath;

	m_edit_previousExtension.GetWindowTextW(m_text_previousExtension);
	m_edit_afterExtension.GetWindowTextW(m_text_afterExtension);

	Conversion extensionConversion = Conversion(m_text_previousExtension, m_text_afterExtension);

	for (int i = 0; i < listboxCount; i++) {
		m_list_filePath.GetText(i, filePath);
		extensionConversion.RenameExtension(filePath);
	}

	MessageBox(_T("ファイルの変換が完了しました。"));

	CListBox* plist = (CListBox*)GetDlgItem(IDC_LIST1);
	plist->ResetContent();

	listBox.clear();
}

void CExtensionChangeDlg::OnBnClickedReferenceFolderButton()
{
	char dir[MAX_PATH] = { '\0' };

	const int tchrSize = sizeof(dir) + 1;
	TCHAR tchrText[tchrSize] = { _T('¥0') };
	int res = MultiByteToWideChar(CP_ACP, MB_PRECOMPOSED, dir, sizeof(dir), tchrText, tchrSize);

	UpdateData(TRUE);

	BOOL bRes = SelectFolder(this->m_hWnd, NULL, tchrText, BIF_RETURNONLYFSDIRS | BIF_NEWDIALOGSTYLE, _T("フォルダーを選択してください。"));

	if (bRes) {
		GetFileList(tchrText,true);
		MessageBox(_T("ファイルの参照が完了しました。"));
	}
}

void CExtensionChangeDlg::OnBnClickedClearButton()
{
	// TODO: ここにコントロール通知ハンドラー コードを追加します。

	CListBox* plist = (CListBox*)GetDlgItem(IDC_LIST1);
	plist->ResetContent();
	listBox.clear();
}

int CALLBACK BrowseCallbackProc(HWND hWnd, UINT uMsg, LPARAM lParam, LPARAM lpData)
{
	switch (uMsg)
	{
	case BFFM_INITIALIZED:
		SendMessage(hWnd, BFFM_SETSELECTION, (WPARAM)TRUE, lpData);
		break;
	case BFFM_SELCHANGED:
		break;
	}
	return 0;
}

BOOL CExtensionChangeDlg::SelectFolder(HWND hWnd,LPCTSTR lpDefFolder,LPTSTR lpSelectPath,UINT nFlag,LPCTSTR lpTitle)
{
	LPMALLOC pMalloc;
	BOOL bRet = FALSE;

	if (SUCCEEDED(SHGetMalloc(&pMalloc))) {
		BROWSEINFO browsInfo;
		ITEMIDLIST *pIDlist;

		memset(&browsInfo, NULL, sizeof(browsInfo));

		browsInfo.hwndOwner = hWnd;
		browsInfo.pidlRoot = NULL;
		browsInfo.pszDisplayName = lpSelectPath;
		browsInfo.lpszTitle = lpTitle;
		browsInfo.ulFlags = nFlag;
		browsInfo.lpfn = &BrowseCallbackProc;
		browsInfo.lParam = (LPARAM)lpDefFolder;
		browsInfo.iImage = (int)NULL;

		pIDlist = SHBrowseForFolder(&browsInfo);
		if(pIDlist) {
			SHGetPathFromIDList(pIDlist, lpSelectPath);
			bRet = TRUE;
			pMalloc->Free(pIDlist);
		}
		pMalloc->Release();
	}
	return bRet;
}

BOOL CExtensionChangeDlg::GetFileList(CString path, bool flag)
{
	// ファイル検索を開始します。
	CFileFind fileFind;
	BOOL bResult = fileFind.FindFile(path);

	// ファイル検索ができない場合、終了します。
	if (!bResult) return FALSE;

	m_edit_previousExtension.GetWindowTextW(m_text_previousExtension);

	// ファイルが検索できる間繰り返します。
	do
	{
		// ファイルを検索します。
		// 次のファイル・ディレクトリがない場合、FALSEが返却されます。
		bResult = fileFind.FindNextFile();

		// "."または".."の場合、次を検索します。
		if (fileFind.IsDots()) continue;

		// 検索した結果がディレクトリの場合
		CString filePath = fileFind.GetFilePath();
		if (fileFind.IsDirectory() && ((((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() == BST_CHECKED) || flag))
		{
			flag = false;
			// サブディレクトリを検索する場合、再帰呼出しします。
			CPath subDir = filePath;
			// ディレクトリ内のすべてのファイル・ディレクトリを対象とするため
			// ワイルドカード"*"を指定します。
			subDir.Append(_T("*"));
			GetFileList(subDir,flag);
		}
		// ファイルの場合
		else
		{
			if (fileFind.IsDirectory()) { //ディレクトリ
				continue;
			}
			else if (listBox.count(filePath) == 1) { //既にリストボックスに存在
				continue;
			}
			//else if (m_text_previousExtension == L"" && filePath.Right(_tcslen(filePath) - filePath.ReverseFind(L'\\') - 1).ReverseFind(L'.') != -1) { //変換前拡張子がなし、判定したいパスの拡張子はあり
			//	continue;
			//}
			//else if (m_text_previousExtension != L"" && filePath.Right(_tcslen(filePath) - filePath.ReverseFind(L'.') - 1) != m_text_previousExtension) { //変換前拡張子があり、変換前拡張子と実際の拡張子が異なる
			//	continue;
			//}
			else {
				listBox.insert(filePath);
				m_list_filePath.AddString(filePath);
			}
		}
	} while (bResult);
	
	return TRUE;
}

void CExtensionChangeDlg::OnDropFiles(HDROP hDropInfo)
{
	// TODO: ここにメッセージ ハンドラー コードを追加するか、既定の処理を呼び出します。

	for (int i = 0; i < DragQueryFile(hDropInfo, -1, NULL, 0); i++) {
		UINT length = DragQueryFile(hDropInfo, i, NULL, 0);

		CString csfile;
		DragQueryFile(hDropInfo, i, csfile.GetBuffer(length + 1), length + 1);
		csfile.ReleaseBuffer();

		GetFileList(csfile, true);

		CDialogEx::OnDropFiles(hDropInfo);
	}
}	