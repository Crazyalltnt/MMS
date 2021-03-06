// CLoginDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MMS.h"
#include "CLoginDlg.h"
#include "afxdialogex.h"


// CLoginDlg 对话框

IMPLEMENT_DYNAMIC(CLoginDlg, CDialogEx)
////////////////

CLoginDlg::CLoginDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_LOGIN, pParent)
	, m_strUser(_T(""))
	, m_strPass(_T(""))
{

}

CLoginDlg::~CLoginDlg()
{
}

void CLoginDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_USER, m_strUser);
	DDX_Text(pDX, IDC_EDIT_PASS, m_strPass);
}


BEGIN_MESSAGE_MAP(CLoginDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDOK, &CLoginDlg::OnBnClickedOk)
END_MESSAGE_MAP()

void CLoginDlg::OnPaint()
{
	CPaintDC dc(this);
	CBitmap   bitmap;
	bitmap.LoadBitmap(IDB_BITMAP2);
	CBrush   brush;
	brush.CreatePatternBrush(&bitmap);
	CBrush*   pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(0, 0, 685, 410);  // 这些参数可以调整图片添加位置和大小
	dc.SelectObject(pOldBrush);
}


// CLoginDlg 消息处理程序



void CLoginDlg::OnBnClickedOk()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData();
	if (m_strUser.IsEmpty() || m_strPass.IsEmpty())
	{
		MessageBox("用户名或者密码不能为空！");
		return;
	}
	m_num++;
	CString strSQL;
	strSQL.Format("select * from [dbo].[Employee] where Authority ='%s' and Password = '%s'", "admi", m_strPass);
	CLoginSet recordset;
	if (!recordset.Open(AFX_DB_USE_DEFAULT_TYPE, strSQL))
	{
		MessageBox("打开数据库失败!", "数据库错误", MB_OK);
		return;
	}
	if (recordset.GetRecordCount() == 0)
	{
		if (m_num == 3)
		{
			MessageBox("密码错误3次,自动退出！");
			CDialog::OnOK();
		}
		else {
			recordset.Close();
			MessageBox("密码错误，请重新输入！");
			m_strPass = "";
			UpdateData(FALSE);
		}

	}
	else {
		MessageBox("登录成功！");
		CDialog::OnOK();

	}

}
