
// MFCCommDlg.cpp: 实现文件
//

#include "pch.h"
#include "framework.h"
#include "MFCComm.h"
#include "MFCCommDlg.h"
#include "afxdialogex.h"
#include "Resource.h"
//#include <functional>

#ifdef _DEBUG
#define new DEBUG_NEW
#endif

//void pushmsg(CString a);

#include "chatserver.h"
CString cstr;
char str[20];
bool isserver = false;
bool is();
// 用于应用程序“关于”菜单项的 CAboutDlg 对话框




class CAboutDlg : public CDialogEx
{
public:
	CAboutDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_ABOUTBOX };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持

// 实现
protected:
	DECLARE_MESSAGE_MAP()
public:
	afx_msg void OnBnClickedSend();
};

CAboutDlg::CAboutDlg() : CDialogEx(IDD_ABOUTBOX)
{
}

void CAboutDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CAboutDlg, CDialogEx)
	//ON_BN_CLICKED(Send, &CAboutDlg::OnBnClickedSend)
END_MESSAGE_MAP()


// CMFCCommDlg 对话框



CMFCCommDlg::CMFCCommDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MFCCOMM_DIALOG, pParent)
	, MsgBox(_T(""))
	, Msgs(_T(""))
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CMFCCommDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	//DDX_Text(pDX, IDC_EDIT1, MsgBox);
	DDX_Control(pDX, IDC_LIST2, MsgList);
	DDX_LBString(pDX, IDC_LIST2, Msgs);
}

BEGIN_MESSAGE_MAP(CMFCCommDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(Send, &CMFCCommDlg::OnBnClickedSend)
	ON_BN_CLICKED(Connect, &CMFCCommDlg::OnBnClickedConnect)
	ON_BN_CLICKED(IDC_CHECK1, &CMFCCommDlg::OnBnClickedCheck1)
	ON_BN_CLICKED(IDC_BUTTON2, &CMFCCommDlg::OnBnClickedButton2)
	ON_BN_CLICKED(IDC_BUTTON1, &CMFCCommDlg::OnBnClickedButton1)
END_MESSAGE_MAP()


// CMFCCommDlg 消息处理程序

BOOL CMFCCommDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	SetDlgItemText(IDC_EDIT1,_T("127.0.0.1"));
	SetDlgItemText(IDC_EDIT2,_T("11451"));

	// 将“关于...”菜单项添加到系统菜单中。

	// IDM_ABOUTBOX 必须在系统命令范围内。
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

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

void CMFCCommDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CMFCCommDlg::OnPaint()
{
	if (IsIconic())
	{
		CPaintDC dc(this); // 用于绘制的设备上下文

		SendMessage(WM_ICONERASEBKGND, reinterpret_cast<WPARAM>(dc.GetSafeHdc()), 0);

		// 使图标在工作区矩形中居中
		int cxIcon = GetSystemMetrics(SM_CXICON);
		int cyIcon = GetSystemMetrics(SM_CYICON);
		CRect rect;
		GetClientRect(&rect);
		int x = (rect.Width() - cxIcon + 1) / 2;
		int y = (rect.Height() - cyIcon + 1) / 2;

		// 绘制图标
		dc.DrawIcon(x, y, m_hIcon);
	}
	else
	{
		CDialogEx::OnPaint();
	}
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CMFCCommDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}


void CMFCCommDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	//SetDlgItemText(IDC_EDIT1, _T("test"));
	//MessageBox(_T("Clicked"));
	CString ret;
	GetDlgItem(IDC_EDIT3)->GetWindowText(cstr);
	Cstring2Char(cstr, str);
	if (isserver) {
		ret = server(cstr);
	}
	else {
		ret = client(cstr);
	}
	MsgList.AddString(ret);
}


void CMFCCommDlg::OnBnClickedConnect()
{
	// TODO: 在此添加控件通知处理程序代码
	//if (is()) MsgList.AddString(_T("yes"));
	//else MsgList.AddString(_T("no"));
	CString ret;
	GetDlgItem(IDC_EDIT2)->GetWindowText(cstr);
	Cstring2Char(cstr, str);
	if (isserver) {
		//GetDlgItem(IDC_EDIT2)->GetWindowText(str);
		ret=setserver(atoi(str));
	}
	else {
		GetDlgItem(IDC_EDIT1)->GetWindowText(cstr);
		ret=setclient(cstr,atoi(str));
	}

	MsgList.AddString(ret);

	thread t([this] { this->receive(); });
	t.detach();
}


void CMFCCommDlg::OnBnClickedCheck1()
{
	if (BST_CHECKED == ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()) isserver=true;
	if (BST_UNCHECKED == ((CButton*)GetDlgItem(IDC_CHECK1))->GetCheck()) isserver = false;
}


void CMFCCommDlg::OnBnClickedButton2()
{
	// TODO: 在此添加控件通知处理程序代码
	// 
	MsgList.ResetContent();
	//std::bind(&receive, this);
	/**
	CString ret;
	if (isserver) {
		ret = serverrecv();
	}
	else {
		ret = clientrecv();
	}
	MsgList.AddString(ret);
	**/
}


void CMFCCommDlg::OnBnClickedButton1()
{
	closes();
	//thread t
	MsgList.AddString(_T("已关闭连接"));
}

void CMFCCommDlg::receive() {
	CString ret;
	MsgList.AddString(_T("启动接收线程"));
	while (1) {
		if (isserver) {
			ret = serverrecv();
		}
		else {
		ret = clientrecv();
		}
		if (ret == "接受失败！\r\n") {
			return;
			MsgList.AddString(_T("结束连接"));
		}

		MsgList.AddString(ret);
	}
}