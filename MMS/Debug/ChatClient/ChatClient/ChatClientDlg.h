
// ChatClientDlg.h: 头文件
//

#pragma once
#include "CMySocket.h"

// CChatClientDlg 对话框
class CChatClientDlg : public CDialogEx
{
// 构造
public:
	CChatClientDlg(CWnd* pParent = nullptr);	// 标准构造函数

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_CHATCLIENT_DIALOG };
#endif

	protected:
	virtual void DoDataExchange(CDataExchange* pDX);	// DDX/DDV 支持


// 实现
protected:
	HICON m_hIcon;

	// 生成的消息映射函数
	virtual BOOL OnInitDialog();
	afx_msg void OnPaint();
	afx_msg HCURSOR OnQueryDragIcon();
	DECLARE_MESSAGE_MAP()
public:
	CListBox m_list;
	CEdit m_input;

	CMySocket * m_client;
	char buff[200];
	CTime m_tm;
	DWORD m_Port;
	CString m_IPAddress;
	afx_msg void OnBnClickedStart();
	afx_msg void OnBnClickedDisconnect();
	afx_msg void OnBnClickedSend();
	afx_msg void OnBnClickedCancel();
};
