
// MMSDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MMS.h"
#include "MMSDlg.h"
#include "afxdialogex.h"

#ifdef _DEBUG
#define new DEBUG_NEW
#endif


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


// CMMSDlg 对话框



CMMSDlg::CMMSDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_MMS_DIALOG, pParent)
{
	m_hIcon = AfxGetApp()->LoadIcon(IDI_ICON1);
}

void CMMSDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
}

BEGIN_MESSAGE_MAP(CMMSDlg, CDialogEx)
	ON_WM_SYSCOMMAND()
	ON_WM_PAINT()
	ON_WM_QUERYDRAGICON()
	ON_BN_CLICKED(IDC_BN_PRODUCT, &CMMSDlg::OnBnClickedBnProduct)
	ON_BN_CLICKED(IDC_BN_PROVIDER, &CMMSDlg::OnBnClickedBnProvider)
	ON_BN_CLICKED(IDC_BN_STOCK, &CMMSDlg::OnBnClickedBnStock)
	ON_BN_CLICKED(IDC_BN_SALE, &CMMSDlg::OnBnClickedBnSale)
	ON_BN_CLICKED(IDC_BN_CLIENT, &CMMSDlg::OnBnClickedBnClient)
	ON_BN_CLICKED(IDC_BN_EMPLOYEE, &CMMSDlg::OnBnClickedBnEmployee)
	ON_BN_CLICKED(IDC_BN_EXIT, &CMMSDlg::OnBnClickedBnExit)
	ON_BN_CLICKED(IDC_BN_ERROR, &CMMSDlg::OnBnClickedBnError)
END_MESSAGE_MAP()


// CMMSDlg 消息处理程序

BOOL CMMSDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();
	//登录界面
	if (m_loginDlg.DoModal() != IDOK)
	{
		OnOK();
	}

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

void CMMSDlg::OnSysCommand(UINT nID, LPARAM lParam)
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

void CMMSDlg::OnPaint()
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
HCURSOR CMMSDlg::OnQueryDragIcon()
{
	return static_cast<HCURSOR>(m_hIcon);
}



void CMMSDlg::OnBnClickedBnProduct()
{
	// TODO: 在此添加控件通知处理程序代码
	CProductDlg dlg;
	dlg.DoModal();
}


void CMMSDlg::OnBnClickedBnProvider()
{
	// TODO: 在此添加控件通知处理程序代码
	CProviderDlg dlg;
	dlg.DoModal();
}


void CMMSDlg::OnBnClickedBnStock()
{
	// TODO: 在此添加控件通知处理程序代码
	CStockDlg dlg;
	dlg.DoModal();
}


void CMMSDlg::OnBnClickedBnSale()
{
	// TODO: 在此添加控件通知处理程序代码
	CSaleDlg dlg;
	dlg.DoModal();
}


void CMMSDlg::OnBnClickedBnClient()
{
	// TODO: 在此添加控件通知处理程序代码
	CClientDlg dlg;
	dlg.DoModal();
}


void CMMSDlg::OnBnClickedBnEmployee()
{
	// TODO: 在此添加控件通知处理程序代码
	CEmployeeDlg dlg;
	dlg.DoModal();
}


void CMMSDlg::OnBnClickedBnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	//int nResponse=MessageBox("是否真的要退出？",MB_YESNO);
	int nResponse = AfxMessageBox("是否真的要退出系统？", MB_YESNO);
	if (nResponse == IDYES)
		CDialog::OnOK();
}


void CMMSDlg::OnBnClickedBnError()
{
	// TODO: 在此添加控件通知处理程序代码
	char buff[MAX_PATH];//用于存放获取的路径信息。
	GetModuleFileName(NULL, buff, MAX_PATH);//第一个参数为句柄，NULL则指向当前程序。第二个参数用于存放地址的指针，第三个参数，系统自带的宏定义。
	CString str = buff;//将buff存放的路径赋给字符串str
	int pos = str.ReverseFind('\\');//查找倒数最后一个“\\”符号
	str = str.Left(pos + 1);//str只获取exe所在文件夹路径
	str=str + "ChatClient\\Debug\\ChatClient.exe";
	//MessageBox(str);//用来调试路径
	ShellExecute(NULL, "open", str, NULL, NULL, SW_SHOWNORMAL);
	
}
