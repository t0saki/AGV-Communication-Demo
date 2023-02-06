
// MFCCommDlg.h: 头文件
//

#pragma once


// CMFCCommDlg 对话框
class CMFCCommDlg : public CDialogEx
{
// 构造
public:
	CMFCCommDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_MFCCOMM_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnSysCommand(UINT nID, LPARAM lParam);
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CString MsgBox;
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedConnect();
	CListBox MsgList;
	afx_msg void OnBnClickedCheck1();
	CString Msgs;
	afx_msg void OnBnClickedButton2();
	afx_msg void OnBnClickedButton1();
	void receive();
};
