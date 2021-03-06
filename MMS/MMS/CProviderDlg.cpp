// CProviderDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MMS.h"
#include "CProviderDlg.h"
#include "afxdialogex.h"


// CProviderDlg 对话框

IMPLEMENT_DYNAMIC(CProviderDlg, CDialogEx)

CProviderDlg::CProviderDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PROVIDER, pParent)
	, m_strPVNo_Q(_T(""))
	, m_strPVNAME_Q(_T(""))
	, m_strPVNo(_T(""))
	, m_strPVName(_T(""))
	, m_strPVCon(_T(""))
	, m_strPVTel(_T(""))
	, m_strPVCode(_T(""))
	, m_strPVNam(_T(""))
	, m_strPVBank(_T(""))
	, m_strPVAcc(_T(""))
{

}

CProviderDlg::~CProviderDlg()
{
}

void CProviderDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PVNo_Q, m_strPVNo_Q);
	DDX_Text(pDX, IDC_EDIT_PVNAME_Q, m_strPVNAME_Q);
	DDX_Text(pDX, IDC_EDIT_PVNo, m_strPVNo);
	DDX_Text(pDX, IDC_EDIT_PVNAME, m_strPVName);
	DDX_Text(pDX, IDC_EDIT_PVCON, m_strPVCon);
	DDX_Text(pDX, IDC_EDIT_PVTEL, m_strPVTel);
	DDX_Text(pDX, IDC_EDIT_PVCODE, m_strPVCode);
	DDX_Text(pDX, IDC_EDIT_PVNAM, m_strPVNam);
	DDX_Text(pDX, IDC_EDIT_PVBANK, m_strPVBank);
	DDX_Text(pDX, IDC_EDIT_PVACC, m_strPVAcc);
}


BEGIN_MESSAGE_MAP(CProviderDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BN_FIRST, &CProviderDlg::OnBnClickedBnFirst)
	ON_BN_CLICKED(IDC_BN_PREV, &CProviderDlg::OnBnClickedBnPrev)
	ON_BN_CLICKED(IDC_BN_NEXT, &CProviderDlg::OnBnClickedBnNext)
	ON_BN_CLICKED(IDC_BN_LAST, &CProviderDlg::OnBnClickedBnLast)
	ON_BN_CLICKED(IDC_BN_QUERY, &CProviderDlg::OnBnClickedBnQuery)
	ON_BN_CLICKED(IDC_BN_ADD, &CProviderDlg::OnBnClickedBnAdd)
	ON_BN_CLICKED(IDC_BN_EDIT, &CProviderDlg::OnBnClickedBnEdit)
	ON_BN_CLICKED(IDC_BN_DELETE, &CProviderDlg::OnBnClickedBnDelete)
	ON_BN_CLICKED(IDC_BN_SAVE, &CProviderDlg::OnBnClickedBnSave)
	ON_BN_CLICKED(IDC_BN_CANCEL, &CProviderDlg::OnBnClickedBnCancel)
	ON_BN_CLICKED(IDC_BN_EXIT, &CProviderDlg::OnBnClickedBnExit)
END_MESSAGE_MAP()

void CProviderDlg::OnPaint()
{
	CPaintDC dc(this);
	CBitmap   bitmap;
	bitmap.LoadBitmap(IDB_BITMAP4);
	CBrush   brush;
	brush.CreatePatternBrush(&bitmap);
	CBrush*   pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(0, 0, 685, 410);  // 这些参数可以调整图片添加位置和大小
	dc.SelectObject(pOldBrush);
}

// CProviderDlg 消息处理程序

void CProviderDlg::ClearEditData(void)
{
	m_strPVNo = "";
	m_strPVName = "";
	m_strPVCon = "";
	m_strPVTel = "";
	m_strPVCode = "";
	m_strPVNam = "";
	m_strPVBank = "";
	m_strPVAcc = "";

	UpdateData(FALSE);
	return;
}


void CProviderDlg::ReadRecord(void)
{
	m_strPVNo = m_rsProviderSet.m_ProviderID;
	m_strPVName = m_rsProviderSet.m_ProviderName;
	m_strPVCon = m_rsProviderSet.m_Contacts;
	m_strPVTel = m_rsProviderSet.m_Telephone;
	m_strPVCode = m_rsProviderSet.m_ZipCode;
	m_strPVNam = m_rsProviderSet.m_Holder;
	m_strPVBank = m_rsProviderSet.m_Bank;
	m_strPVAcc = m_rsProviderSet.m_Account;

	UpdateData(FALSE);
	return;
}


void CProviderDlg::WriteRecord(void)
{
	UpdateData(TRUE);

	m_rsProviderSet.m_ProviderID = m_strPVNo;
	m_rsProviderSet.m_ProviderName = m_strPVName;
	m_rsProviderSet.m_Contacts = m_strPVCon;
	m_rsProviderSet.m_Telephone = m_strPVTel;
	m_rsProviderSet.m_ZipCode = m_strPVCode;
	m_rsProviderSet.m_Holder = m_strPVNam;
	m_rsProviderSet.m_Bank = m_strPVBank;
	m_rsProviderSet.m_Account = m_strPVAcc;

}


void CProviderDlg::SetMoveBNState(void)
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


void CProviderDlg::SetEditState(void)
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

		pWnd = GetDlgItem(IDC_EDIT_PVNo);
		if (m_bAdd)
			pWnd->EnableWindow(TRUE);
		else
			pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_PVNAME);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_PVCON);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_PVTEL);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_PVCODE);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_PVNAM);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_PVBANK);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_PVACC);
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

		pWnd = GetDlgItem(IDC_EDIT_PVNo);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_PVNAME);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_PVCON);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_PVTEL);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_PVCODE);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_PVNAM);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_PVBANK);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_PVACC);
		pWnd->EnableWindow(FALSE);
	}
	return;
}

BOOL CProviderDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_rsProviderSet.Open(AFX_DB_USE_DEFAULT_TYPE);
	if (!m_rsProviderSet.IsOpen())
	{
		AfxMessageBox("数据库打开失败!");
		return TRUE;
	}
	else if (m_rsProviderSet.IsBOF())
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
		m_rsProviderSet.MoveFirst();
		m_bFirst = true;
		m_bLast = false;
		ReadRecord();
		SetMoveBNState();
		SetEditState();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CProviderDlg::OnBnClickedBnFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsProviderSet.MoveFirst();
	m_bFirst = true;
	m_bLast = false;
	SetMoveBNState();
	ReadRecord();
}


void CProviderDlg::OnBnClickedBnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsProviderSet.MovePrev();
	if (m_rsProviderSet.IsBOF())
	{
		m_rsProviderSet.MoveFirst();
		m_bFirst = TRUE;
	}
	SetMoveBNState();
	ReadRecord();
}


void CProviderDlg::OnBnClickedBnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsProviderSet.MoveNext();
	if (m_rsProviderSet.IsEOF())
	{
		m_rsProviderSet.MoveLast();
		m_bLast = true;
	}
	SetMoveBNState();
	ReadRecord();
}


void CProviderDlg::OnBnClickedBnLast()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsProviderSet.MoveLast();
	m_bFirst = false;
	m_bLast = true;
	SetMoveBNState();
	ReadRecord();
}


void CProviderDlg::OnBnClickedBnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strPVNo_Q.IsEmpty() && m_strPVNAME_Q.IsEmpty())
	{
		m_rsProviderSet.m_strFilter = "";
		m_rsProviderSet.Requery();
		if (m_rsProviderSet.IsBOF())
		{
			AfxMessageBox("数据集空！");
			m_bEmpty = true;
			ClearEditData();
			SetMoveBNState();
		}
		else
		{
			m_bEmpty = false;
			m_rsProviderSet.MoveFirst();
			m_bFirst = true;
			m_bLast = false;
			ReadRecord();
			SetMoveBNState();
		}
		return;
	}
	BOOL mbSNoQInput = FALSE;
	if (!m_strPVNo_Q.IsEmpty())
	{
		m_rsProviderSet.m_strFilter = "ProviderID='" + m_strPVNo_Q;
		m_rsProviderSet.m_strFilter = m_rsProviderSet.m_strFilter + "'";

		mbSNoQInput = TRUE;
	}
	if (!m_strPVNAME_Q.IsEmpty())
	{
		if (mbSNoQInput)
		{
			m_rsProviderSet.m_strFilter = m_rsProviderSet.m_strFilter
				+ " AND ProviderName='";
			m_rsProviderSet.m_strFilter = m_rsProviderSet.m_strFilter
				+ m_strPVNAME_Q;
			m_rsProviderSet.m_strFilter = m_rsProviderSet.m_strFilter
				+ "'";
		}
		else
		{
			m_rsProviderSet.m_strFilter = "ProviderName='" + m_strPVNAME_Q;
			m_rsProviderSet.m_strFilter = m_rsProviderSet.m_strFilter + "'";

		}

	}
	m_rsProviderSet.Requery();
	if (m_rsProviderSet.IsEOF())
	{
		AfxMessageBox("没有查到相关记录！");
		m_bEmpty = true;
		ClearEditData();
		SetMoveBNState();
	}
	else
	{
		m_bEmpty = false;
		m_rsProviderSet.MoveFirst();
		m_bFirst = true;
		ReadRecord();
		SetMoveBNState();
	}

}


void CProviderDlg::OnBnClickedBnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	ClearEditData();
	m_bEdit = true;
	m_bAdd = true;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_PVNo);
	pWnd->SetFocus();
}


void CProviderDlg::OnBnClickedBnEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bEdit = true;
	m_bAdd = false;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_PVNAME);
	pWnd->SetFocus();
}


void CProviderDlg::OnBnClickedBnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if (AfxMessageBox("确定要删除此条记录吗？", MB_YESNO) != IDYES)
		return;
	m_rsProviderSet.Delete();
	//m_rsSCChoiceSet.MoveNext();
	m_rsProviderSet.Requery();
	if (m_rsProviderSet.IsBOF())
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


void CProviderDlg::OnBnClickedBnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strPVNo.IsEmpty() || m_strPVName.IsEmpty())
	{
		AfxMessageBox("请输入相应数据！");
		CWnd *pWnd;
		pWnd = GetDlgItem(IDC_EDIT_PVNo);
		pWnd->SetFocus();
		return;
	}
	if (m_bAdd)
	{
		m_rsProviderSet.AddNew();
	}
	else
	{
		m_rsProviderSet.Edit();
	}
	WriteRecord();
	m_rsProviderSet.Update();
	m_rsProviderSet.Requery();
	m_rsProviderSet.MoveFirst();
	m_bFirst = true;
	m_bLast = false;
	m_bAdd = false;
	m_bEdit = false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();

}


void CProviderDlg::OnBnClickedBnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bAdd = false;
	m_bEdit = false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CProviderDlg::OnBnClickedBnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
