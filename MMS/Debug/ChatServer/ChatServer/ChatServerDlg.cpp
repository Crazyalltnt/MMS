
// ChatServerDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "ChatServerDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


// CChatServerDlg 对话框



CChatServerDlg::CChatServerDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_CHATSERVER_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDR_MAINFRAME);
}

void CChatServerDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Control(pDX, IDC_HISTORY, m_list);
	DDX_Control(pDX, IDC_INPUT, m_input);
}

BEGIN_MESSAGE_MAP(CChatServerDlg, CDialogEx)
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_START, &CChatServerDlg::OnBnClickedStart)
	ON_BN_CLICKED(IDC_DISCONNECT, &CChatServerDlg::OnBnClickedDisconnect)
	ON_BN_CLICKED(IDC_SEND, &CChatServerDlg::OnBnClickedSend)
	ON_BN_CLICKED(IDC_CANCEL, &CChatServerDlg::OnBnClickedCancel)
END_MESSAGE_MAP()


// CChatServerDlg 消息处理程序

BOOL CChatServerDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// 设置此对话框的图标。  当应用程序主窗口不是对话框时，框架将自动
	//  执行此操作
	SetIcon(m_hIcon, TRUE);			// 设置大图标
	SetIcon(m_hIcon, FALSE);		// 设置小图标

	// TODO: 在此添加额外的初始化代码
	GetDlgItem(IDC_PORT)->SetWindowText("5000");
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE);
	GetDlgItem(IDC_INPUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE);

	return TRUE;  // 除非将焦点设置到控件，否则返回 TRUE
}

// 如果向对话框添加最小化按钮，则需要下面的代码
//  来绘制该图标。  对于使用文档/视图模型的 MFC 应用程序，
//  这将由框架自动完成。

void CChatServerDlg::OnPaint()
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
HCURSOR CChatServerDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CChatServerDlg::OnBnClickedStart()
{
	// TODO: 在此添加控件通知处理程序代码
	GetDlgItem(IDC_START)->EnableWindow(FALSE);
	CString temp;
	GetDlgItem(IDC_PORT)->GetWindowText(temp);
	UINT port = atoi(temp.GetBuffer());
	//1st Create 
	m_server = new CServerSocket;
	if ((*m_server).Create(port) == 0)
	{
		static int code = (*m_server).GetLastError();
		CString err; err.Format("%d", code);
		CString error = "Create Error Code= ";
		error += err;
		MessageBox(error);
		return;
	}

	//2nd Listen 
	if ((*m_server).Listen() == 0)
	{
		static int code = (*m_server).GetLastError();
		CString err;
		err.Format("%d", code);
		CString error = "Create Error Code= ";
		error += err;
		MessageBox(error);
		return;
	}

	GetDlgItem(IDC_START)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(TRUE);
	GetDlgItem(IDC_INPUT)->EnableWindow(TRUE);
	GetDlgItem(IDC_SEND)->EnableWindow(TRUE);
	CString str; m_tm = CTime::GetCurrentTime();
	str = m_tm.Format("%X "); str += "建立服务!";
	m_list.AddString(str);
	UpdateData(FALSE);
}


void CChatServerDlg::OnBnClickedDisconnect()
{
	// TODO: 在此添加控件通知处理程序代码
	(*m_server).Close();
	delete m_server;
	delete m_client;
	CString str;
	m_tm = CTime::GetCurrentTime();
	str = m_tm.Format("%X");
	str += " 服务中断!";
	m_list.AddString(str);
	UpdateData(FALSE);
	GetDlgItem(IDC_START)->EnableWindow(TRUE);
	GetDlgItem(IDC_INPUT)->EnableWindow(FALSE);
	GetDlgItem(IDC_SEND)->EnableWindow(FALSE);
	GetDlgItem(IDC_DISCONNECT)->EnableWindow(FALSE);
}


void CChatServerDlg::OnBnClickedSend()
{
	// TODO: 在此添加控件通知处理程序代码
	m_input.GetWindowText(buff, 200);
	(*m_client).Send(buff, 200);
	CString temp1 = " 我：";
	CString temp2 = buff;
	CString str;
	m_tm = CTime::GetCurrentTime();
	str = m_tm.Format("%X");
	temp1 = str + temp1;
	temp1 += temp2;
	CChatServerDlg* dlg = (CChatServerDlg*)AfxGetApp()->GetMainWnd();
	m_list.AddString(temp1);
	UpdateData(FALSE);
	m_input.SetWindowText("");
}


void CChatServerDlg::OnBnClickedCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnCancel();
}
