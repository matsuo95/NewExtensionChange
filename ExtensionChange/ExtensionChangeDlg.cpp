
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
	ON_BN_CLICKED(IDC_BUTTON4, &CExtensionChangeDlg::OnBnClickedReferenceFileButton)
	ON_BN_CLICKED(IDC_BUTTON3, &CExtensionChangeDlg::OnBnClickedConversionFileButton)
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

/// ファイル参照ボタンを押したときに呼び出される関数
void CExtensionChangeDlg::OnBnClickedReferenceFileButton()
{
	UpdateData();

	CString			filePath = _T("");
	CFileDialog     selDlg(TRUE, NULL, NULL,OFN_ALLOWMULTISELECT );

	if (selDlg.DoModal() == IDOK) {
		POSITION filepathPosition = selDlg.GetStartPosition();
		while (filepathPosition)
		{
			filePath = selDlg.GetNextPathName(filepathPosition);
			FileSearch(filePath);
		}
	}

	return;
}

/// フォルダ参照ボタンを押したときに呼び出される関数
void CExtensionChangeDlg::OnBnClickedReferenceFolderButton()
{
	UpdateData();
	TCHAR folderPath[MAX_PATH];

	BOOL selectResult = SelectFolder(this->m_hWnd, NULL, folderPath,BIF_NEWDIALOGSTYLE, _T("フォルダーを選択してください。"));

	if (selectResult) {
		FileSearch(folderPath);
	}
}

/// フォルダ参照ダイアログを開き、フォルダパスを得るための関数
BOOL CExtensionChangeDlg::SelectFolder(HWND hWnd,LPCTSTR lpDefFolder,LPTSTR lpSelectPath,UINT nFlag,LPCTSTR lpTitle)
{
	LPMALLOC pMalloc;
	BOOL selectResult = FALSE;

	if (SUCCEEDED(SHGetMalloc(&pMalloc))) {
		BROWSEINFO browsInfo;
		ITEMIDLIST *pIDlist;

		memset(&browsInfo, NULL, sizeof(browsInfo));

		browsInfo.hwndOwner = hWnd;
		browsInfo.pidlRoot = NULL;
		browsInfo.pszDisplayName = lpSelectPath;
		browsInfo.lpszTitle = lpTitle;
		browsInfo.ulFlags = nFlag;
		browsInfo.lpfn = NULL;
		browsInfo.lParam = (LPARAM)lpDefFolder;
		browsInfo.iImage = (int)NULL;

		pIDlist = SHBrowseForFolder(&browsInfo);
		if(pIDlist) {
			if (SHGetPathFromIDList(pIDlist, lpSelectPath)) {
				selectResult = TRUE;
			};
			pMalloc->Free(pIDlist);
		}
		pMalloc->Release();
	}
	return selectResult;
}

/// ファイルまたはフォルダをドラッグアンドドロップしたときに呼び出される関数
void CExtensionChangeDlg::OnDropFiles(HDROP hDropInfo)
{
	UpdateData();
	CString path;
	for (UINT i = 0; i < DragQueryFile(hDropInfo, -1, NULL, 0); i++) {
		UINT bufferLength = DragQueryFile(hDropInfo, i, NULL, 0);

		DragQueryFile(hDropInfo, i, path.GetBuffer(bufferLength), bufferLength + 1);

		FileSearch(path);

		path.ReleaseBuffer();
	}
}

/// フォルダ内のファイルを探索するための関数
void CExtensionChangeDlg::FileSearch(CString strPath)
{
	CPath cPath = strPath;
	if (cPath.IsDirectory()) {
		cPath.Append(_T("*"));
	}
	else {
		OutputFilePath(cPath);
		return;
	}

	CFileFind fileFind;
	BOOL searchResult = fileFind.FindFile(cPath);

	while(searchResult)
	{
		searchResult = fileFind.FindNextFile();

		if (fileFind.IsDots()) continue;

		CString path = fileFind.GetFilePath();

		if (fileFind.IsDirectory()) 
		{
			if (((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck() == BST_CHECKED) {
				FileSearch(path);
			}
		}
		else 
		{
			OutputFilePath(path);
		}
	}

	return;
}

/// 変換ボタンを押したときに呼び出される関数
void CExtensionChangeDlg::OnBnClickedConversionFileButton()
{
	int listboxCount = m_list_filePath.GetCount();

	if (listboxCount == 0) return;

	CString filePath;

	UpdateData();

	Conversion extensionConversion = Conversion(m_text_previousExtension, m_text_afterExtension);

	int errNo = 0, errCount = 0;

	for (int i = 0; i < listboxCount; i++) {
		m_list_filePath.GetText(i, filePath);
		errNo = extensionConversion.RenameExtension(filePath);
		if (errNo) errCount++;
	}

	if (errCount == 0) {
		MessageBox(_T("全てのファイルの変換が完了しました"));
	}
	else {
		CString message;
		message.Format(_T("%d個のファイルの変換に失敗しました"), errCount);
		AfxMessageBox(message);
	}

	DeleteListbox();
}

/// クリアボタンを押したときに呼び出される関数
void CExtensionChangeDlg::OnBnClickedClearButton()
{
	DeleteListbox();
}

/// リストボックスに表示されているパスをすべて削除する関数
void CExtensionChangeDlg::DeleteListbox() 
{
	CListBox* plist = (CListBox*)GetDlgItem(IDC_LIST1);
	plist->ResetContent();
	m_listBox.clear();
}

/// ファイルパスをリストボックスに出力する関数
void CExtensionChangeDlg::OutputFilePath(CString filePath)
{
	CString fileName = filePath.Right(_tcslen(filePath) - filePath.ReverseFind(_T('\\')) - 1);
	CString fileExtension = fileName.Right(_tcslen(fileName) - fileName.ReverseFind(_T('.')) - 1);

	if (m_listBox.count(filePath) == 1) { //既にリストボックスに存在
		return;
	}
	else if (m_text_previousExtension == _T("") && fileName.ReverseFind(_T('.')) != -1) { //変換前拡張子がなし、判定したいファイルの拡張子はあり
		return;
	}
	else if (m_text_previousExtension != _T("") &&  m_text_previousExtension != fileExtension) { //変換前拡張子があり、変換前拡張子と実際の拡張子が異なる
		return;
	}
	else {
		m_listBox.insert(filePath);
		m_list_filePath.AddString(filePath);
	}
}