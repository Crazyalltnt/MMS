// CSaleDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MMS.h"
#include "CSaleDlg.h"
#include "afxdialogex.h"


// CSaleDlg 对话框

IMPLEMENT_DYNAMIC(CSaleDlg, CDialogEx)

CSaleDlg::CSaleDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_SALE, pParent)
	, m_strSAID_Q(_T(""))
	, m_strSANo_Q(_T(""))
	, m_strSAid(_T(""))
	, m_strSANo(_T(""))
	, m_strSAPrice(0.0)
	, m_strSADate(_T(""))
	, m_strSANum(0.0)
	, m_strSADis(0)
	, m_strSACid(_T(""))
	, m_strSAEid(_T(""))
{

}

CSaleDlg::~CSaleDlg()
{
}

void CSaleDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_SAID_Q, m_strSAID_Q);
	DDX_Text(pDX, IDC_EDIT_SANo_Q, m_strSANo_Q);
	DDX_Text(pDX, IDC_EDIT_SAID, m_strSAid);
	DDX_Text(pDX, IDC_EDIT_SANo, m_strSANo);
	DDX_Text(pDX, IDC_EDIT_SAPrice, m_strSAPrice);
	DDX_Text(pDX, IDC_EDIT_SADATE, m_strSADate);
	DDX_Text(pDX, IDC_EDIT_SANUM, m_strSANum);
	DDX_Text(pDX, IDC_EDIT_SADIS, m_strSADis);
	DDX_Text(pDX, IDC_EDIT_SACID, m_strSACid);
	DDX_Text(pDX, IDC_EDIT_SAEID, m_strSAEid);
}


BEGIN_MESSAGE_MAP(CSaleDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BN_FIRST, &CSaleDlg::OnBnClickedBnFirst)
	ON_BN_CLICKED(IDC_BN_PREV, &CSaleDlg::OnBnClickedBnPrev)
	ON_BN_CLICKED(IDC_BN_NEXT, &CSaleDlg::OnBnClickedBnNext)
	ON_BN_CLICKED(IDC_BN_LAST, &CSaleDlg::OnBnClickedBnLast)
	ON_BN_CLICKED(IDC_BN_QUERY, &CSaleDlg::OnBnClickedBnQuery)
	ON_BN_CLICKED(IDC_BN_ADD, &CSaleDlg::OnBnClickedBnAdd)
	ON_BN_CLICKED(IDC_BN_EDIT, &CSaleDlg::OnBnClickedBnEdit)
	ON_BN_CLICKED(IDC_BN_DELETE, &CSaleDlg::OnBnClickedBnDelete)
	ON_BN_CLICKED(IDC_BN_SAVE, &CSaleDlg::OnBnClickedBnSave)
	ON_BN_CLICKED(IDC_BN_CANCEL, &CSaleDlg::OnBnClickedBnCancel)
	ON_BN_CLICKED(IDC_BN_EXIT, &CSaleDlg::OnBnClickedBnExit)
END_MESSAGE_MAP()

void CSaleDlg::OnPaint()
{
	CPaintDC dc(this);
	CBitmap   bitmap;
	bitmap.LoadBitmap(IDB_BITMAP6);
	CBrush   brush;
	brush.CreatePatternBrush(&bitmap);
	CBrush*   pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(0, 0, 685, 410);  // 这些参数可以调整图片添加位置和大小
	dc.SelectObject(pOldBrush);
}

// CSaleDlg 消息处理程序

void CSaleDlg::ClearEditData(void)
{
	m_strSAid = "";
	m_strSANo = "";
	m_strSAPrice = 0.0;
	m_strSADate = "";
	m_strSANum = 0.0;
	m_strSADis = 0;
	m_strSACid = "";
	m_strSAEid = "";

	UpdateData(FALSE);
	return;
}


void CSaleDlg::ReadRecord(void)
{
	m_strSAid = m_rsSaleSet.m_SaleID;
	m_strSANo = m_rsSaleSet.m_ProductID;
	m_strSAPrice = m_rsSaleSet.m_SalePrice;
	m_strSADate = m_rsSaleSet.m_SaleDate.Format("%Y-%m-%d");
	m_strSANum = m_rsSaleSet.m_SaleQuantity;
	m_strSADis = m_rsSaleSet.m_Discount;
	m_strSACid = m_rsSaleSet.m_ClientID;
	m_strSAEid = m_rsSaleSet.m_EmployeeID;

	UpdateData(FALSE);
	return;
}


void CSaleDlg::WriteRecord(void)
{
	UpdateData(TRUE);

	m_rsSaleSet.m_SaleID = m_strSAid;
	m_rsSaleSet.m_ProductID = m_strSANo;
	m_rsSaleSet.m_SalePrice = m_strSAPrice;
	m_rsSaleSet.m_SaleQuantity = m_strSANum;
	m_rsSaleSet.m_Discount = m_strSADis;
	m_rsSaleSet.m_ClientID = m_strSACid;
	m_rsSaleSet.m_EmployeeID = m_strSAEid;

	int a, b, c;
	CString   timestrA = m_strSADate;
	sscanf_s(timestrA.GetBuffer(timestrA.GetLength()), "%d-%d-%d", &a, &b, &c);
	CTime   timeA(a, b, c, 0, 0, 0);
	m_rsSaleSet.m_SaleDate = timeA;
}


void CSaleDlg::SetMoveBNState(void)
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


void CSaleDlg::SetEditState(void)
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

		pWnd = GetDlgItem(IDC_EDIT_SAID);
		if (m_bAdd)
			pWnd->EnableWindow(TRUE);
		else
			pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_SANo);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_SAPrice);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_SADATE);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_SANUM);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_SADIS);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_SACID);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_SAEID);
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

		pWnd = GetDlgItem(IDC_EDIT_SAID);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_SANo);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_SAPrice);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_SADATE);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_SANUM);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_SADIS);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_SACID);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_SAEID);
		pWnd->EnableWindow(FALSE);
	}
	return;
}

BOOL CSaleDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_rsSaleSet.Open(AFX_DB_USE_DEFAULT_TYPE);
	if (!m_rsSaleSet.IsOpen())
	{
		AfxMessageBox("数据库打开失败!");
		return TRUE;
	}
	else if (m_rsSaleSet.IsBOF())
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
		m_rsSaleSet.MoveFirst();
		m_bFirst = true;
		m_bLast = false;
		ReadRecord();
		SetMoveBNState();
		SetEditState();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CSaleDlg::OnBnClickedBnFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsSaleSet.MoveFirst();
	m_bFirst = true;
	m_bLast = false;
	SetMoveBNState();
	ReadRecord();
}


void CSaleDlg::OnBnClickedBnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsSaleSet.MovePrev();
	if (m_rsSaleSet.IsBOF())
	{
		m_rsSaleSet.MoveFirst();
		m_bFirst = TRUE;
	}
	SetMoveBNState();
	ReadRecord();
}


void CSaleDlg::OnBnClickedBnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsSaleSet.MoveNext();
	if (m_rsSaleSet.IsEOF())
	{
		m_rsSaleSet.MoveLast();
		m_bLast = true;
	}
	SetMoveBNState();
	ReadRecord();
}


void CSaleDlg::OnBnClickedBnLast()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsSaleSet.MoveLast();
	m_bFirst = false;
	m_bLast = true;
	SetMoveBNState();
	ReadRecord();
}


void CSaleDlg::OnBnClickedBnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strSAID_Q.IsEmpty() && m_strSANo_Q.IsEmpty())
	{
		m_rsSaleSet.m_strFilter = "";
		m_rsSaleSet.Requery();
		if (m_rsSaleSet.IsBOF())
		{
			AfxMessageBox("数据集空！");
			m_bEmpty = true;
			ClearEditData();
			SetMoveBNState();
		}
		else
		{
			m_bEmpty = false;
			m_rsSaleSet.MoveFirst();
			m_bFirst = true;
			m_bLast = false;
			ReadRecord();
			SetMoveBNState();
		}
		return;
	}
	BOOL mbSAIDQInput = FALSE;
	if (!m_strSAID_Q.IsEmpty())
	{
		m_rsSaleSet.m_strFilter = "SaleID='" + m_strSAID_Q;
		m_rsSaleSet.m_strFilter = m_rsSaleSet.m_strFilter + "'";

		mbSAIDQInput = TRUE;
	}
	if (!m_strSANo_Q.IsEmpty())
	{
		if (mbSAIDQInput)
		{
			m_rsSaleSet.m_strFilter = m_rsSaleSet.m_strFilter
				+ " AND	ProductID='";
			m_rsSaleSet.m_strFilter = m_rsSaleSet.m_strFilter
				+ m_strSANo_Q;
			m_rsSaleSet.m_strFilter = m_rsSaleSet.m_strFilter
				+ "'";
		}
		else
		{
			m_rsSaleSet.m_strFilter = "ProductID='" + m_strSANo_Q;
			m_rsSaleSet.m_strFilter = m_rsSaleSet.m_strFilter + "'";

		}

	}
	m_rsSaleSet.Requery();
	if (m_rsSaleSet.IsEOF())
	{
		AfxMessageBox("没有查到相关记录！");
		m_bEmpty = true;
		ClearEditData();
		SetMoveBNState();
	}
	else
	{
		m_bEmpty = false;
		m_rsSaleSet.MoveFirst();
		m_bFirst = true;
		ReadRecord();
		SetMoveBNState();
	}

}


void CSaleDlg::OnBnClickedBnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	ClearEditData();
	m_bEdit = true;
	m_bAdd = true;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_SAID);
	pWnd->SetFocus();
}


void CSaleDlg::OnBnClickedBnEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bEdit = true;
	m_bAdd = false;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_SANo);
	pWnd->SetFocus();
}


void CSaleDlg::OnBnClickedBnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if (AfxMessageBox("确定要删除此条记录吗？", MB_YESNO) != IDYES)
		return;
	m_rsSaleSet.Delete();
	//m_rsSCChoiceSet.MoveNext();
	m_rsSaleSet.Requery();
	if (m_rsSaleSet.IsBOF())
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


void CSaleDlg::OnBnClickedBnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strSAid.IsEmpty() || m_strSANo.IsEmpty())
	{
		AfxMessageBox("请输入相应数据！");
		CWnd *pWnd;
		pWnd = GetDlgItem(IDC_EDIT_SAID);
		pWnd->SetFocus();
		return;
	}
	if (m_bAdd)
	{
		m_rsSaleSet.AddNew();
	}
	else
	{
		m_rsSaleSet.Edit();
	}
	WriteRecord();
	m_rsSaleSet.Update();
	m_rsSaleSet.Requery();
	m_rsSaleSet.MoveFirst();
	m_bFirst = true;
	m_bLast = false;
	m_bAdd = false;
	m_bEdit = false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CSaleDlg::OnBnClickedBnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bAdd = false;
	m_bEdit = false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CSaleDlg::OnBnClickedBnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
