
// ChatClientDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ChatClient.h"
#include "ChatClientDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatClientDlg 对话框



CChatClientDlg::CChatClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATCLIENT_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HISTORY, m_list);
	DDX_Control(pDX, IDC_INPUT, m_input);
}

BEGIN_MESSAGE_MAP(CChatClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CChatClientDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_DISCONNECT, &CChatClientDlg::OnBnClickedDisconnect)
	ON_BN_CLICKED(IDC_SEND, &CChatClientDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_CANCEL, &CChatClientDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CChatClientDlg 消息处理程序

BOOL CChatClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_INPUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_IPADDRESS)->SetWindowText((LPCTSTR)"127.0.0.1");
	GetDlgItem(IDC_PORT)->SetWindowText((LPCTSTR)"5000");

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatClientDlg::OnPaint()
{
	CPaintDC dc(this);
	CBitmap   bitmap;
	bitmap.LoadBitmap(IDB_BITMAP1);
	CBrush   brush;
	brush.CreatePatternBrush(&bitmap);
	CBrush*   pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(0, 0, 685, 410);  // 这些参数可以调整图片添加位置和大小
	dc.SelectObject(pOldBrush);
}

//当用户拖动最小化窗口时系统调用此函数取得光标
//显示。
HCURSOR CChatClientDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatClientDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEND)->EnableWindow(TRUE);
	CString temp1, temp2;
	GetDlgItem(IDC_IPADDRESS)->GetWindowText(temp1);
	CString m_IPAddress = temp1.GetBuffer(temp1.GetLength());
	GetDlgItem(IDC_PORT)->GetWindowText(temp2);
	int m_Port = atoi(temp2);
	m_client = new CMySocket;
	if ((*m_client).Create() == 0)
	{
		CString errcode;
		errcode.Format("%d", GetLastError());
		m_list.AddString(errcode);
		UpdateData(FALSE);
	}
	m_client->Connect(m_IPAddress, m_Port);
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(FALSE);
	GetDlgItem(IDC_PORT)->EnableWindow(FALSE);
	GetDlgItem(IDC_INPUT)->EnableWindow(TRUE);
}


void CChatClientDlg::OnBnClickedDisconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	(*m_client).Close();
	delete m_client;
	GetDlgItem(IDC_IPADDRESS)->EnableWindow(TRUE);
	GetDlgItem(IDC_PORT)->EnableWindow(TRUE);
	GetDlgItem(IDC_INPUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE);
	CString str;
	m_tm = CTime::GetCurrentTime();
	str = m_tm.Format("%X ");
	str += "从服务器断开!";
	m_list.AddString(str);
	UpdateData(FALSE);
}


void CChatClientDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	m_input.GetWindowText(buff, 200);
	CString temp1 = "我：";
	CString temp2 = buff;
	CString formatbuff = "#c#s#" + (CString)buff;
	(*m_client).Send(formatbuff, 200, 0);
	CString str;
	m_tm = CTime::GetCurrentTime();
	str = m_tm.Format("%X ");
	temp1 = str + temp1;
	temp1 += temp2;
	m_list.AddString(temp1);
	UpdateData(FALSE);
	m_input.SetWindowText("");
}


void CChatClientDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
