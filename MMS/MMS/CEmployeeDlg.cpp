// CEmployeeDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MMS.h"
#include "CEmployeeDlg.h"
#include "afxdialogex.h"


// CEmployeeDlg 对话框

IMPLEMENT_DYNAMIC(CEmployeeDlg, CDialogEx)

CEmployeeDlg::CEmployeeDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_EMPLOYEE, pParent)
	, m_strENo_Q(_T(""))
	, m_strENAME_Q(_T(""))
	, m_strENo(_T(""))
	, m_strEName(_T(""))
	, m_strEAu(_T(""))
	, m_strEPass(_T(""))
{

}

CEmployeeDlg::~CEmployeeDlg()
{
}

void CEmployeeDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_ENo_Q, m_strENo_Q);
	DDX_Text(pDX, IDC_EDIT_ENAME_Q, m_strENAME_Q);
	DDX_Text(pDX, IDC_EDIT_ENo, m_strENo);
	DDX_Text(pDX, IDC_EDIT_ENAME, m_strEName);
	DDX_Text(pDX, IDC_EDIT_EAU, m_strEAu);
	DDX_Text(pDX, IDC_EDIT_EPASS, m_strEPass);
}


BEGIN_MESSAGE_MAP(CEmployeeDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BN_FIRST, &CEmployeeDlg::OnBnClickedBnFirst)
	ON_BN_CLICKED(IDC_BN_PREV, &CEmployeeDlg::OnBnClickedBnPrev)
	ON_BN_CLICKED(IDC_BN_NEXT, &CEmployeeDlg::OnBnClickedBnNext)
	ON_BN_CLICKED(IDC_BN_LAST, &CEmployeeDlg::OnBnClickedBnLast)
	ON_BN_CLICKED(IDC_BN_QUERY, &CEmployeeDlg::OnBnClickedBnQuery)
	ON_BN_CLICKED(IDC_BN_ADD, &CEmployeeDlg::OnBnClickedBnAdd)
	ON_BN_CLICKED(IDC_BN_EDIT, &CEmployeeDlg::OnBnClickedBnEdit)
	ON_BN_CLICKED(IDC_BN_DELETE, &CEmployeeDlg::OnBnClickedBnDelete)
	ON_BN_CLICKED(IDC_BN_SAVE, &CEmployeeDlg::OnBnClickedBnSave)
	ON_BN_CLICKED(IDC_BN_CANCEL, &CEmployeeDlg::OnBnClickedBnCancel)
	ON_BN_CLICKED(IDC_BN_EXIT, &CEmployeeDlg::OnBnClickedBnExit)
END_MESSAGE_MAP()

void CEmployeeDlg::OnPaint()
{
	CPaintDC dc(this);
	CBitmap   bitmap;
	bitmap.LoadBitmap(IDB_BITMAP8);
	CBrush   brush;
	brush.CreatePatternBrush(&bitmap);
	CBrush*   pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(0, 0, 497, 307);  // 这些参数可以调整图片添加位置和大小
	dc.SelectObject(pOldBrush);
}

// CEmployeeDlg 消息处理程序

void CEmployeeDlg::ClearEditData(void)
{
	m_strENo = "";
	m_strEName = "";
	m_strEAu = "";
	m_strEPass = "";

	UpdateData(FALSE);
	return;
}


void CEmployeeDlg::ReadRecord(void)
{
	m_strENo = m_rsEmployeeSet.m_EmployeeID;
	m_strEName = m_rsEmployeeSet.m_EmployeeName;
	m_strEAu = m_rsEmployeeSet.m_Authority;
	m_strEPass = m_rsEmployeeSet.m_Password;

	UpdateData(FALSE);
	return;
}


void CEmployeeDlg::WriteRecord(void)
{
	UpdateData(TRUE);

	m_rsEmployeeSet.m_EmployeeID = m_strENo;
	m_rsEmployeeSet.m_EmployeeName = m_strEName;
	m_rsEmployeeSet.m_Authority = m_strEAu;
	m_rsEmployeeSet.m_Password = m_strEPass;

}


void CEmployeeDlg::SetMoveBNState(void)
{
	CWnd *pWnd;
	if (m_bEmpty || m_bEdit)
	{
		pWnd = GetDlgItem(IDC_BN_FIRST);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_PREV);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_LAST);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_NEXT);
		pWnd->EnableWindow(FALSE);
		return;
	}
	if (m_bFirst)
	{
		pWnd = GetDlgItem(IDC_BN_FIRST);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_PREV);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_LAST);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_NEXT);
		pWnd->EnableWindow(TRUE);
	}
	else if (m_bLast)
	{
		pWnd = GetDlgItem(IDC_BN_FIRST);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_PREV);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_LAST);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_NEXT);
		pWnd->EnableWindow(FALSE);
	}
	else
	{
		pWnd = GetDlgItem(IDC_BN_FIRST);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_PREV);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_LAST);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_NEXT);
		pWnd->EnableWindow(TRUE);
	}
	return;
}


void CEmployeeDlg::SetEditState(void)
{
	CWnd *pWnd;
	if (m_bEdit)
	{
		pWnd = GetDlgItem(IDC_BN_ADD);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_EDIT);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_DELETE);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_QUERY);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_SAVE);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_CANCEL);
		pWnd->EnableWindow(TRUE);

		pWnd = GetDlgItem(IDC_EDIT_ENo);
		if (m_bAdd)
			pWnd->EnableWindow(TRUE);
		else
			pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_ENAME);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_EAU);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_EPASS);
		pWnd->EnableWindow(TRUE);
	}
	else
	{
		pWnd = GetDlgItem(IDC_BN_ADD);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_EDIT);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_DELETE);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_QUERY);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_BN_SAVE);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_BN_CANCEL);
		pWnd->EnableWindow(FALSE);

		pWnd = GetDlgItem(IDC_EDIT_ENo);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_ENAME);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_EAU);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_EPASS);
		pWnd->EnableWindow(FALSE);
	}
	return;
}

BOOL CEmployeeDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_rsEmployeeSet.Open(AFX_DB_USE_DEFAULT_TYPE);
	if (!m_rsEmployeeSet.IsOpen())
	{
		AfxMessageBox("数据库打开失败!");
		return TRUE;
	}
	else if (m_rsEmployeeSet.IsBOF())
	{
		AfxMessageBox("数据集空！");
		m_bEmpty = true;
		ClearEditData();
		SetMoveBNState();
		SetEditState();
	}
	else
	{
		m_bEmpty = false;
		m_rsEmployeeSet.MoveFirst();
		m_bFirst = true;
		m_bLast = false;
		ReadRecord();
		SetMoveBNState();
		SetEditState();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CEmployeeDlg::OnBnClickedBnFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsEmployeeSet.MoveFirst();
	m_bFirst = true;
	m_bLast = false;
	SetMoveBNState();
	ReadRecord();
}


void CEmployeeDlg::OnBnClickedBnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsEmployeeSet.MovePrev();
	if (m_rsEmployeeSet.IsBOF())
	{
		m_rsEmployeeSet.MoveFirst();
		m_bFirst = TRUE;
	}
	SetMoveBNState();
	ReadRecord();
}


void CEmployeeDlg::OnBnClickedBnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsEmployeeSet.MoveNext();
	if (m_rsEmployeeSet.IsEOF())
	{
		m_rsEmployeeSet.MoveLast();
		m_bLast = true;
	}
	SetMoveBNState();
	ReadRecord();
}


void CEmployeeDlg::OnBnClickedBnLast()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsEmployeeSet.MoveLast();
	m_bFirst = false;
	m_bLast = true;
	SetMoveBNState();
	ReadRecord();
}


void CEmployeeDlg::OnBnClickedBnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strENo_Q.IsEmpty() && m_strENAME_Q.IsEmpty())
	{
		m_rsEmployeeSet.m_strFilter = "";
		m_rsEmployeeSet.Requery();
		if (m_rsEmployeeSet.IsBOF())
		{
			AfxMessageBox("数据集空！");
			m_bEmpty = true;
			ClearEditData();
			SetMoveBNState();
		}
		else
		{
			m_bEmpty = false;
			m_rsEmployeeSet.MoveFirst();
			m_bFirst = true;
			m_bLast = false;
			ReadRecord();
			SetMoveBNState();
		}
		return;
	}
	BOOL mbENoQInput = FALSE;
	if (!m_strENo_Q.IsEmpty())
	{
		m_rsEmployeeSet.m_strFilter = "EmployeeID='" + m_strENo_Q;
		m_rsEmployeeSet.m_strFilter = m_rsEmployeeSet.m_strFilter + "'";

		mbENoQInput = TRUE;
	}
	if (!m_strENAME_Q.IsEmpty())
	{
		if (mbENoQInput)
		{
			m_rsEmployeeSet.m_strFilter = m_rsEmployeeSet.m_strFilter
				+ " AND EmployeeName='";
			m_rsEmployeeSet.m_strFilter = m_rsEmployeeSet.m_strFilter
				+ m_strENAME_Q;
			m_rsEmployeeSet.m_strFilter = m_rsEmployeeSet.m_strFilter
				+ "'";
		}
		else
		{
			m_rsEmployeeSet.m_strFilter = "EmployeeName='" + m_strENAME_Q;
			m_rsEmployeeSet.m_strFilter = m_rsEmployeeSet.m_strFilter + "'";

		}

	}
	m_rsEmployeeSet.Requery();
	if (m_rsEmployeeSet.IsEOF())
	{
		AfxMessageBox("没有查到相关记录！");
		m_bEmpty = true;
		ClearEditData();
		SetMoveBNState();
	}
	else
	{
		m_bEmpty = false;
		m_rsEmployeeSet.MoveFirst();
		m_bFirst = true;
		ReadRecord();
		SetMoveBNState();
	}

}


void CEmployeeDlg::OnBnClickedBnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	ClearEditData();
	m_bEdit = true;
	m_bAdd = true;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_ENo);
	pWnd->SetFocus();
}


void CEmployeeDlg::OnBnClickedBnEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bEdit = true;
	m_bAdd = false;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_ENAME);
	pWnd->SetFocus();
}


void CEmployeeDlg::OnBnClickedBnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if (AfxMessageBox("确定要删除此条记录吗？", MB_YESNO) != IDYES)
		return;
	m_rsEmployeeSet.Delete();
	//m_rsSCChoiceSet.MoveNext();
	m_rsEmployeeSet.Requery();
	if (m_rsEmployeeSet.IsBOF())
	{
		AfxMessageBox("表中已没有记录了！");
		ClearEditData();
		m_bEmpty = true;
		SetMoveBNState();
		return;
	}
	m_bFirst = true;
	m_bLast = false;
	ReadRecord();
	SetMoveBNState();
}


void CEmployeeDlg::OnBnClickedBnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strENo.IsEmpty() || m_strEName.IsEmpty())
	{
		AfxMessageBox("请输入相应数据！");
		CWnd *pWnd;
		pWnd = GetDlgItem(IDC_EDIT_ENo);
		pWnd->SetFocus();
		return;
	}
	if (m_bAdd)
	{
		m_rsEmployeeSet.AddNew();
	}
	else
	{
		m_rsEmployeeSet.Edit();
	}
	WriteRecord();
	m_rsEmployeeSet.Update();
	m_rsEmployeeSet.Requery();
	m_rsEmployeeSet.MoveFirst();
	m_bFirst = true;
	m_bLast = false;
	m_bAdd = false;
	m_bEdit = false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CEmployeeDlg::OnBnClickedBnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bAdd = false;
	m_bEdit = false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CEmployeeDlg::OnBnClickedBnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
