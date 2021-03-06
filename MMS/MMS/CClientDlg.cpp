// CClientDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MMS.h"
#include "CClientDlg.h"
#include "afxdialogex.h"


// CClientDlg 对话框

IMPLEMENT_DYNAMIC(CClientDlg, CDialogEx)

CClientDlg::CClientDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_CLIENT, pParent)
	, m_strCNo_Q(_T(""))
	, m_strCCON_Q(_T(""))
	, m_strCNo(_T(""))
	, m_strCCon(_T(""))
	, m_strCTel(_T(""))
	, m_strCCode(_T(""))
	, m_strCAddr(_T(""))
{

}

CClientDlg::~CClientDlg()
{
}

void CClientDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_CNo_Q, m_strCNo_Q);
	DDX_Text(pDX, IDC_EDIT_CCON_Q, m_strCCON_Q);
	DDX_Text(pDX, IDC_EDIT_CNo, m_strCNo);
	DDX_Text(pDX, IDC_EDIT_CCON, m_strCCon);
	DDX_Text(pDX, IDC_EDIT_CTEL, m_strCTel);
	DDX_Text(pDX, IDC_EDIT_CCODE, m_strCCode);
	DDX_Text(pDX, IDC_EDIT_CADDR, m_strCAddr);
}


BEGIN_MESSAGE_MAP(CClientDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BN_FIRST, &CClientDlg::OnBnClickedBnFirst)
	ON_BN_CLICKED(IDC_BN_PREV, &CClientDlg::OnBnClickedBnPrev)
	ON_BN_CLICKED(IDC_BN_NEXT, &CClientDlg::OnBnClickedBnNext)
	ON_BN_CLICKED(IDC_BN_LAST, &CClientDlg::OnBnClickedBnLast)
	ON_BN_CLICKED(IDC_BN_QUERY, &CClientDlg::OnBnClickedBnQuery)
	ON_BN_CLICKED(IDC_BN_ADD, &CClientDlg::OnBnClickedBnAdd)
	ON_BN_CLICKED(IDC_BN_EDIT, &CClientDlg::OnBnClickedBnEdit)
	ON_BN_CLICKED(IDC_BN_DELETE, &CClientDlg::OnBnClickedBnDelete)
	ON_BN_CLICKED(IDC_BN_SAVE, &CClientDlg::OnBnClickedBnSave)
	ON_BN_CLICKED(IDC_BN_CANCEL, &CClientDlg::OnBnClickedBnCancel)
	ON_BN_CLICKED(IDC_BN_EXIT, &CClientDlg::OnBnClickedBnExit)
	ON_BN_CLICKED(IDC_BN_PHONE, &CClientDlg::OnBnClickedBnPhone)
END_MESSAGE_MAP()

void CClientDlg::OnPaint()
{
	CPaintDC dc(this);
	CBitmap   bitmap;
	bitmap.LoadBitmap(IDB_BITMAP7);
	CBrush   brush;
	brush.CreatePatternBrush(&bitmap);
	CBrush*   pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(0, 0, 604, 345);  // 这些参数可以调整图片添加位置和大小
	dc.SelectObject(pOldBrush);
}

// CClientDlg 消息处理程序

void CClientDlg::ClearEditData(void)
{
	m_strCNo = "";
	m_strCCon = "";
	m_strCTel = "";
	m_strCCode = "";
	m_strCAddr = "";

	UpdateData(FALSE);
	return;
}


void CClientDlg::ReadRecord(void)
{
	m_strCNo = m_rsClientSet.m_ClientID;
	m_strCCon = m_rsClientSet.m_Contacts;
	m_strCTel = m_rsClientSet.m_Telephone;
	m_strCCode = m_rsClientSet.m_ZipCode;
	m_strCAddr = m_rsClientSet.m_Address;

	UpdateData(FALSE);
	return;
}


void CClientDlg::WriteRecord(void)
{
	UpdateData(TRUE);

	m_rsClientSet.m_ClientID = m_strCNo;
	m_rsClientSet.m_Contacts = m_strCCon;
	m_rsClientSet.m_Telephone = m_strCTel;
	m_rsClientSet.m_ZipCode = m_strCCode;
	m_rsClientSet.m_Address = m_strCAddr;

}


void CClientDlg::SetMoveBNState(void)
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


void CClientDlg::SetEditState(void)
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

		pWnd = GetDlgItem(IDC_EDIT_CNo);
		if (m_bAdd)
			pWnd->EnableWindow(TRUE);
		else
			pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_CCON);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_CTEL);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_CCODE);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_CADDR);
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

		pWnd = GetDlgItem(IDC_EDIT_CNo);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_CCON);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_CTEL);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_CCODE);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_CADDR);
		pWnd->EnableWindow(FALSE);
	}
	return;
}

BOOL CClientDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_rsClientSet.Open(AFX_DB_USE_DEFAULT_TYPE);
	if (!m_rsClientSet.IsOpen())
	{
		AfxMessageBox("数据库打开失败!");
		return TRUE;
	}
	else if (m_rsClientSet.IsBOF())
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
		m_rsClientSet.MoveFirst();
		m_bFirst = true;
		m_bLast = false;
		ReadRecord();
		SetMoveBNState();
		SetEditState();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CClientDlg::OnBnClickedBnFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsClientSet.MoveFirst();
	m_bFirst = true;
	m_bLast = false;
	SetMoveBNState();
	ReadRecord();
}


void CClientDlg::OnBnClickedBnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsClientSet.MovePrev();
	if (m_rsClientSet.IsBOF())
	{
		m_rsClientSet.MoveFirst();
		m_bFirst = TRUE;
	}
	SetMoveBNState();
	ReadRecord();
}


void CClientDlg::OnBnClickedBnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsClientSet.MoveNext();
	if (m_rsClientSet.IsEOF())
	{
		m_rsClientSet.MoveLast();
		m_bLast = true;
	}
	SetMoveBNState();
	ReadRecord();
}


void CClientDlg::OnBnClickedBnLast()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsClientSet.MoveLast();
	m_bFirst = false;
	m_bLast = true;
	SetMoveBNState();
	ReadRecord();
}


void CClientDlg::OnBnClickedBnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strCNo_Q.IsEmpty() && m_strCCON_Q.IsEmpty())
	{
		m_rsClientSet.m_strFilter = "";
		m_rsClientSet.Requery();
		if (m_rsClientSet.IsBOF())
		{
			AfxMessageBox("数据集空！");
			m_bEmpty = true;
			ClearEditData();
			SetMoveBNState();
		}
		else
		{
			m_bEmpty = false;
			m_rsClientSet.MoveFirst();
			m_bFirst = true;
			m_bLast = false;
			ReadRecord();
			SetMoveBNState();
		}
		return;
	}
	BOOL mbCNoQInput = FALSE;
	if (!m_strCNo_Q.IsEmpty())
	{
		m_rsClientSet.m_strFilter = "ClientID='" + m_strCNo_Q;
		m_rsClientSet.m_strFilter = m_rsClientSet.m_strFilter + "'";

		mbCNoQInput = TRUE;
	}
	if (!m_strCCON_Q.IsEmpty())
	{
		if (mbCNoQInput)
		{
			m_rsClientSet.m_strFilter = m_rsClientSet.m_strFilter
				+ " AND Contacts='";
			m_rsClientSet.m_strFilter = m_rsClientSet.m_strFilter
				+ m_strCCON_Q;
			m_rsClientSet.m_strFilter = m_rsClientSet.m_strFilter
				+ "'";
		}
		else
		{
			m_rsClientSet.m_strFilter = "Contacts='" + m_strCCON_Q;
			m_rsClientSet.m_strFilter = m_rsClientSet.m_strFilter + "'";

		}

	}
	m_rsClientSet.Requery();
	if (m_rsClientSet.IsEOF())
	{
		AfxMessageBox("没有查到相关记录！");
		m_bEmpty = true;
		ClearEditData();
		SetMoveBNState();
	}
	else
	{
		m_bEmpty = false;
		m_rsClientSet.MoveFirst();
		m_bFirst = true;
		ReadRecord();
		SetMoveBNState();
	}

}


void CClientDlg::OnBnClickedBnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	ClearEditData();
	m_bEdit = true;
	m_bAdd = true;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_CNo);
	pWnd->SetFocus();
}


void CClientDlg::OnBnClickedBnEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bEdit = true;
	m_bAdd = false;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_CCON);
	pWnd->SetFocus();
}


void CClientDlg::OnBnClickedBnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if (AfxMessageBox("确定要删除此条记录吗？", MB_YESNO) != IDYES)
		return;
	m_rsClientSet.Delete();
	//m_rsSCChoiceSet.MoveNext();
	m_rsClientSet.Requery();
	if (m_rsClientSet.IsBOF())
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


void CClientDlg::OnBnClickedBnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strCNo.IsEmpty() || m_strCCon.IsEmpty())
	{
		AfxMessageBox("请输入相应数据！");
		CWnd *pWnd;
		pWnd = GetDlgItem(IDC_EDIT_CNo);
		pWnd->SetFocus();
		return;
	}
	if (m_bAdd)
	{
		m_rsClientSet.AddNew();
	}
	else
	{
		m_rsClientSet.Edit();
	}
	WriteRecord();
	m_rsClientSet.Update();
	m_rsClientSet.Requery();
	m_rsClientSet.MoveFirst();
	m_bFirst = true;
	m_bLast = false;
	m_bAdd = false;
	m_bEdit = false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CClientDlg::OnBnClickedBnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bAdd = false;
	m_bEdit = false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CClientDlg::OnBnClickedBnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}


void CClientDlg::OnBnClickedBnPhone()
{
	// TODO: 在此添加控件通知处理程序代码
	MessageBox("请确保您使用独立版Skype");
	ShellExecute(NULL, "open", "D:\\phone\\Skype.exe", NULL, NULL, SW_SHOWNORMAL);
	//WinExec("C:\\Program Files(x86)\\Skype\\Phone\\Skype.exe", SW_SHOW);  // 打开记事本  
}
