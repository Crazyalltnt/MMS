// CStockDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MMS.h"
#include "CStockDlg.h"
#include "afxdialogex.h"


// CStockDlg 对话框

IMPLEMENT_DYNAMIC(CStockDlg, CDialogEx)

CStockDlg::CStockDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_STOCK, pParent)
	, m_strSTNo_Q(_T(""))
	, m_strSTNo(_T(""))
	, m_strSTPrice(0.0)
	, m_strSTNum(0.0)
	, m_strSTPRNo(_T(""))
	, m_strSTInv(0.0)
	, m_strSTDate(_T(""))
{

}

CStockDlg::~CStockDlg()
{
}

void CStockDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_STNo_Q, m_strSTNo_Q);
	DDX_Text(pDX, IDC_EDIT_STNo, m_strSTNo);
	DDX_Text(pDX, IDC_EDIT_STPrice, m_strSTPrice);
	DDX_Text(pDX, IDC_EDIT_STNUM, m_strSTNum);
	DDX_Text(pDX, IDC_EDIT_STPRNo, m_strSTPRNo);
	DDX_Text(pDX, IDC_EDIT_STINV, m_strSTInv);
	DDX_Text(pDX, IDC_EDIT_STDATE, m_strSTDate);
}


BEGIN_MESSAGE_MAP(CStockDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BN_FIRST, &CStockDlg::OnBnClickedBnFirst)
	ON_BN_CLICKED(IDC_BN_PREV, &CStockDlg::OnBnClickedBnPrev)
	ON_BN_CLICKED(IDC_BN_NEXT, &CStockDlg::OnBnClickedBnNext)
	ON_BN_CLICKED(IDC_BN_LAST, &CStockDlg::OnBnClickedBnLast)
	ON_BN_CLICKED(IDC_BN_ADD, &CStockDlg::OnBnClickedBnAdd)
	ON_BN_CLICKED(IDC_BN_QUERY, &CStockDlg::OnBnClickedBnQuery)
	ON_BN_CLICKED(IDC_BN_EDIT, &CStockDlg::OnBnClickedBnEdit)
	ON_BN_CLICKED(IDC_BN_DELETE, &CStockDlg::OnBnClickedBnDelete)
	ON_BN_CLICKED(IDC_BN_SAVE, &CStockDlg::OnBnClickedBnSave)
	ON_BN_CLICKED(IDC_BN_CANCEL, &CStockDlg::OnBnClickedBnCancel)
	ON_BN_CLICKED(IDC_BN_EXIT, &CStockDlg::OnBnClickedBnExit)
END_MESSAGE_MAP()

void CStockDlg::OnPaint()
{
	CPaintDC dc(this);
	CBitmap   bitmap;
	bitmap.LoadBitmap(IDB_BITMAP5);
	CBrush   brush;
	brush.CreatePatternBrush(&bitmap);
	CBrush*   pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(0, 0, 615, 330);  // 这些参数可以调整图片添加位置和大小
	dc.SelectObject(pOldBrush);
}

// CStockDlg 消息处理程序

void CStockDlg::ClearEditData(void)
{
	m_strSTNo = "";
	m_strSTPrice = 0.0;
	m_strSTNum = 0.0;
	m_strSTPRNo = "";
	m_strSTInv = 0.0;
	m_strSTDate = "";
	

	UpdateData(FALSE);
	return;
}


void CStockDlg::ReadRecord(void)
{
	m_strSTNo = m_rsStockSet.m_ProductID;
	m_strSTPrice = m_rsStockSet.m_StockPrice;
	m_strSTNum = m_rsStockSet.m_StockQuantity;
	m_strSTPRNo = m_rsStockSet.m_ProviderID;
	m_strSTInv = m_rsStockSet.m_Inventory;
	m_strSTDate = m_rsStockSet.m_StockDate.Format("%Y-%m-%d");

	UpdateData(FALSE);
	return;
}


void CStockDlg::WriteRecord(void)
{
	UpdateData(TRUE);

	m_rsStockSet.m_ProductID = m_strSTNo;
	m_rsStockSet.m_StockPrice = m_strSTPrice;
	m_rsStockSet.m_StockQuantity = m_strSTNum;
	m_rsStockSet.m_ProviderID = m_strSTPRNo;
	m_rsStockSet.m_Inventory = m_strSTInv;
	
	int a, b, c;
	CString   timestrT = m_strSTDate;
	sscanf_s(timestrT.GetBuffer(timestrT.GetLength()), "%d-%d-%d", &a, &b, &c);
	CTime   timeT(a, b, c, 0, 0, 0);
	m_rsStockSet.m_StockDate = timeT;

}


void CStockDlg::SetMoveBNState(void)
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


void CStockDlg::SetEditState(void)
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

		pWnd = GetDlgItem(IDC_EDIT_STNo);
		if (m_bAdd)
			pWnd->EnableWindow(TRUE);
		else
			pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_STPrice);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_STNUM);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_STPRNo);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_STINV);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_STDATE);
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

		pWnd = GetDlgItem(IDC_EDIT_STNo);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_STPrice);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_STNUM);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_STPRNo);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_STINV);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_STDATE);
		pWnd->EnableWindow(FALSE);
	}
	return;
}

BOOL CStockDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_rsStockSet.Open(AFX_DB_USE_DEFAULT_TYPE);
	if (!m_rsStockSet.IsOpen())
	{
		AfxMessageBox("数据库打开失败!");
		return TRUE;
	}
	else if (m_rsStockSet.IsBOF())
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
		m_rsStockSet.MoveFirst();
		m_bFirst = true;
		m_bLast = false;
		ReadRecord();
		SetMoveBNState();
		SetEditState();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}

void CStockDlg::OnBnClickedBnFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsStockSet.MoveFirst();
	m_bFirst = true;
	m_bLast = false;
	SetMoveBNState();
	ReadRecord();
}


void CStockDlg::OnBnClickedBnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsStockSet.MovePrev();
	if (m_rsStockSet.IsBOF())
	{
		m_rsStockSet.MoveFirst();
		m_bFirst = TRUE;
	}
	SetMoveBNState();
	ReadRecord();
}


void CStockDlg::OnBnClickedBnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsStockSet.MoveNext();
	if (m_rsStockSet.IsEOF())
	{
		m_rsStockSet.MoveLast();
		m_bLast = true;
	}
	SetMoveBNState();
	ReadRecord();
}


void CStockDlg::OnBnClickedBnLast()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsStockSet.MoveLast();
	m_bFirst = false;
	m_bLast = true;
	SetMoveBNState();
	ReadRecord();
}


void CStockDlg::OnBnClickedBnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	ClearEditData();
	m_bEdit = true;
	m_bAdd = true;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_STNo);
	pWnd->SetFocus();
}


void CStockDlg::OnBnClickedBnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strSTNo_Q.IsEmpty())
	{
		m_rsStockSet.m_strFilter = "";
		m_rsStockSet.Requery();
		if (m_rsStockSet.IsBOF())
		{
			AfxMessageBox("数据集空！");
			m_bEmpty = true;
			ClearEditData();
			SetMoveBNState();
		}
		else
		{
			m_bEmpty = false;
			m_rsStockSet.MoveFirst();
			m_bFirst = true;
			m_bLast = false;
			ReadRecord();
			SetMoveBNState();
		}
		return;
	}
	BOOL mbSNoQInput = FALSE;
	if (!m_strSTNo_Q.IsEmpty())
	{
		m_rsStockSet.m_strFilter = "ProductID='" + m_strSTNo_Q;
		m_rsStockSet.m_strFilter = m_rsStockSet.m_strFilter + "'";

		mbSNoQInput = TRUE;
	}
	
	m_rsStockSet.Requery();
	if (m_rsStockSet.IsEOF())
	{
		AfxMessageBox("没有查到相关记录！");
		m_bEmpty = true;
		ClearEditData();
		SetMoveBNState();
	}
	else
	{
		m_bEmpty = false;
		m_rsStockSet.MoveFirst();
		m_bFirst = true;
		ReadRecord();
		SetMoveBNState();
	}

}


void CStockDlg::OnBnClickedBnEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bEdit = true;
	m_bAdd = false;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_STNo);
	pWnd->SetFocus();
}


void CStockDlg::OnBnClickedBnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if (AfxMessageBox("确定要删除此条记录吗？", MB_YESNO) != IDYES)
		return;
	m_rsStockSet.Delete();
	//m_rsSCChoiceSet.MoveNext();
	m_rsStockSet.Requery();
	if (m_rsStockSet.IsBOF())
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


void CStockDlg::OnBnClickedBnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strSTNo.IsEmpty())
	{
		AfxMessageBox("请输入相应数据！");
		CWnd *pWnd;
		pWnd = GetDlgItem(IDC_EDIT_STNo);
		pWnd->SetFocus();
		return;
	}
	if (m_bAdd)
	{
		m_rsStockSet.AddNew();
	}
	else
	{
		m_rsStockSet.Edit();
	}
	WriteRecord();
	m_rsStockSet.Update();
	m_rsStockSet.Requery();
	m_rsStockSet.MoveFirst();
	m_bFirst = true;
	m_bLast = false;
	m_bAdd = false;
	m_bEdit = false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CStockDlg::OnBnClickedBnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bAdd = false;
	m_bEdit = false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CStockDlg::OnBnClickedBnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
