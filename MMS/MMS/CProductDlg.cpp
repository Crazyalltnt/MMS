// CProductDlg.cpp: 实现文件
//

#include "stdafx.h"
#include "MMS.h"
#include "CProductDlg.h"
#include "afxdialogex.h"


// CProductDlg 对话框

IMPLEMENT_DYNAMIC(CProductDlg, CDialogEx)

CProductDlg::CProductDlg(CWnd* pParent /*=nullptr*/)
	: CDialogEx(IDD_DIALOG_PRODUCT, pParent)
	, m_strPNo_Q(_T(""))
	, m_strPNAME_Q(_T(""))
	, m_strPNo(_T(""))
	, m_strPName(_T(""))
	, m_strPPrice(0.0)
	, m_strPStd(_T(""))
	, m_strPDes(_T(""))
	, m_strPRNo(_T(""))
{

}

CProductDlg::~CProductDlg()
{
}

void CProductDlg::DoDataExchange(CDataExchange* pDX)
{
	CDialogEx::DoDataExchange(pDX);
	DDX_Text(pDX, IDC_EDIT_PNo_Q, m_strPNo_Q);
	DDX_Text(pDX, IDC_EDIT_PNAME_Q, m_strPNAME_Q);
	DDX_Text(pDX, IDC_EDIT_PNo, m_strPNo);
	DDX_Text(pDX, IDC_EDIT_PNAME, m_strPName);
	DDX_Text(pDX, IDC_EDIT_PPrice, m_strPPrice);
	DDX_Text(pDX, IDC_EDIT_PSTD, m_strPStd);
	DDX_Text(pDX, IDC_EDIT_PDES, m_strPDes);
	DDX_Text(pDX, IDC_EDIT_PRNo, m_strPRNo);
}


BEGIN_MESSAGE_MAP(CProductDlg, CDialogEx)
	ON_WM_PAINT()
	ON_BN_CLICKED(IDC_BN_ADD, &CProductDlg::OnBnClickedBnAdd)
	ON_BN_CLICKED(IDC_BN_FIRST, &CProductDlg::OnBnClickedBnFirst)
	ON_BN_CLICKED(IDC_BN_LAST, &CProductDlg::OnBnClickedBnLast)
	ON_BN_CLICKED(IDC_BN_EDIT, &CProductDlg::OnBnClickedBnEdit)
	ON_BN_CLICKED(IDC_BN_QUERY, &CProductDlg::OnBnClickedBnQuery)
	ON_BN_CLICKED(IDC_BN_PREV, &CProductDlg::OnBnClickedBnPrev)
	ON_BN_CLICKED(IDC_BN_NEXT, &CProductDlg::OnBnClickedBnNext)
	ON_BN_CLICKED(IDC_BN_EDIT, &CProductDlg::OnBnClickedBnEdit)
	ON_BN_CLICKED(IDC_BN_DELETE, &CProductDlg::OnBnClickedBnDelete)
	ON_BN_CLICKED(IDC_BN_SAVE, &CProductDlg::OnBnClickedBnSave)
	ON_BN_CLICKED(IDC_BN_CANCEL, &CProductDlg::OnBnClickedBnCancel)
	ON_BN_CLICKED(IDC_BN_EXIT, &CProductDlg::OnBnClickedBnExit)
END_MESSAGE_MAP()

void CProductDlg::OnPaint()
{
	CPaintDC dc(this);
	CBitmap   bitmap;
	bitmap.LoadBitmap(IDB_BITMAP3);
	CBrush   brush;
	brush.CreatePatternBrush(&bitmap);
	CBrush*   pOldBrush = dc.SelectObject(&brush);
	dc.Rectangle(0, 0, 664, 370);  // 这些参数可以调整图片添加位置和大小
	dc.SelectObject(pOldBrush);
}

// CProductDlg 消息处理程序

//清空对话框中显示商品信息的编辑框控件
void CProductDlg::ClearEditData(void)
{
	m_strPNo = "";
	m_strPName = "";
	m_strPPrice = 0.0;
	m_strPStd= "";
	m_strPDes = "";
	m_strPRNo = "";

	UpdateData(FALSE);
	return;
}


//将域数据成员的值传递给对话框控件显示出来
void CProductDlg::ReadRecord(void)
{
	m_strPNo = m_rsProductSet.m_ProductID;
	m_strPName = m_rsProductSet.m_ProductName;
	m_strPPrice = m_rsProductSet.m_ProductPrice;
	m_strPStd = m_rsProductSet.m_Standard;
	m_strPDes = m_rsProductSet.m_Description;
	m_strPRNo = m_rsProductSet.m_ProviderID;

	UpdateData(FALSE);
	return;
}


//将控件中的信息传递给域数据成员
void CProductDlg::WriteRecord(void)
{
	UpdateData(TRUE);

	m_rsProductSet.m_ProductID = m_strPNo;
	m_rsProductSet.m_ProductName = m_strPName;
	m_rsProductSet.m_ProductPrice = m_strPPrice;
	m_rsProductSet.m_Standard = m_strPStd;
	m_rsProductSet.m_Description = m_strPDes;
	m_rsProductSet.m_ProviderID = m_strPRNo;

}


void CProductDlg::SetMoveBNState(void)
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


//根据对数据库的操作类型设置编辑框的可编辑状态
void CProductDlg::SetEditState(void)
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

		pWnd = GetDlgItem(IDC_EDIT_PNo);
		if (m_bAdd)
			pWnd->EnableWindow(TRUE);
		else
			pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_PNAME);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_PPrice);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_PSTD);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_PDES);
		pWnd->EnableWindow(TRUE);
		pWnd = GetDlgItem(IDC_EDIT_PRNo);
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

		pWnd = GetDlgItem(IDC_EDIT_PNo);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_PNAME);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_PPrice);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_PSTD);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_PDES);
		pWnd->EnableWindow(FALSE);
		pWnd = GetDlgItem(IDC_EDIT_PRNo);
		pWnd->EnableWindow(FALSE);
	}
	return;
}

BOOL CProductDlg::OnInitDialog()
{
	CDialogEx::OnInitDialog();

	// TODO:  在此添加额外的初始化
	m_rsProductSet.Open(AFX_DB_USE_DEFAULT_TYPE);
	if (!m_rsProductSet.IsOpen())
	{
		AfxMessageBox("数据库打开失败!");
		return TRUE;
	}
	else if (m_rsProductSet.IsBOF())
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
		m_rsProductSet.MoveFirst();
		m_bFirst = true;
		m_bLast = false;
		ReadRecord();
		SetMoveBNState();
		SetEditState();
	}

	return TRUE;  // return TRUE unless you set the focus to a control
				  // 异常: OCX 属性页应返回 FALSE
}


void CProductDlg::OnBnClickedBnFirst()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsProductSet.MoveFirst();
	m_bFirst = true;
	m_bLast = false;
	SetMoveBNState();
	ReadRecord();
}


void CProductDlg::OnBnClickedBnPrev()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsProductSet.MovePrev();
	if (m_rsProductSet.IsBOF())
	{
		m_rsProductSet.MoveFirst();
		m_bFirst = TRUE;
	}
	SetMoveBNState();
	ReadRecord();
}


void CProductDlg::OnBnClickedBnNext()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bFirst = false;
	m_bLast = false;
	m_rsProductSet.MoveNext();
	if (m_rsProductSet.IsEOF())
	{
		m_rsProductSet.MoveLast();
		m_bLast = true;
	}
	SetMoveBNState();
	ReadRecord();
}


void CProductDlg::OnBnClickedBnLast()
{
	// TODO: 在此添加控件通知处理程序代码
	m_rsProductSet.MoveLast();
	m_bFirst = false;
	m_bLast = true;
	SetMoveBNState();
	ReadRecord();
}



void CProductDlg::OnBnClickedBnQuery()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strPNo_Q.IsEmpty() && m_strPNAME_Q.IsEmpty())
	{
		m_rsProductSet.m_strFilter = "";
		m_rsProductSet.Requery();
		if (m_rsProductSet.IsBOF())
		{
			AfxMessageBox("数据集空！");
			m_bEmpty = true;
			ClearEditData();
			SetMoveBNState();
		}
		else
		{
			m_bEmpty = false;
			m_rsProductSet.MoveFirst();
			m_bFirst = true;
			m_bLast = false;
			ReadRecord();
			SetMoveBNState();
		}
		return;
	}
	BOOL mbPNoQInput = FALSE;
	if (!m_strPNo_Q.IsEmpty())
	{
		m_rsProductSet.m_strFilter = "ProductID='" + m_strPNo_Q;
		m_rsProductSet.m_strFilter = m_rsProductSet.m_strFilter + "'";

		mbPNoQInput = TRUE;
	}
	if (!m_strPNAME_Q.IsEmpty())
	{
		if (mbPNoQInput)
		{
			m_rsProductSet.m_strFilter = m_rsProductSet.m_strFilter
				+ " AND ProductName='";
			m_rsProductSet.m_strFilter = m_rsProductSet.m_strFilter
				+ m_strPNAME_Q;
			m_rsProductSet.m_strFilter = m_rsProductSet.m_strFilter
				+ "'";
		}
		else
		{
			m_rsProductSet.m_strFilter = "ProductName='" + m_strPNAME_Q;
			m_rsProductSet.m_strFilter = m_rsProductSet.m_strFilter + "'";

		}

	}
	m_rsProductSet.Requery();
	if (m_rsProductSet.IsEOF())
	{
		AfxMessageBox("没有查到相关记录！");
		m_bEmpty = true;
		ClearEditData();
		SetMoveBNState();
	}
	else
	{
		m_bEmpty = false;
		m_rsProductSet.MoveFirst();
		m_bFirst = true;
		ReadRecord();
		SetMoveBNState();
	}
}


void CProductDlg::OnBnClickedBnAdd()
{
	// TODO: 在此添加控件通知处理程序代码
	ClearEditData();
	m_bEdit = true;
	m_bAdd = true;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_PNo);
	pWnd->SetFocus();
}


void CProductDlg::OnBnClickedBnEdit()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bEdit = true;
	m_bAdd = false;
	SetMoveBNState();
	SetEditState();
	CWnd *pWnd;
	pWnd = GetDlgItem(IDC_EDIT_PNAME);
	pWnd->SetFocus();
}


void CProductDlg::OnBnClickedBnDelete()
{
	// TODO: 在此添加控件通知处理程序代码
	if (AfxMessageBox("确定要删除此条记录吗？", MB_YESNO) != IDYES)
		return;
	m_rsProductSet.Delete();
	m_rsProductSet.Requery();
	if (m_rsProductSet.IsBOF())
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


void CProductDlg::OnBnClickedBnSave()
{
	// TODO: 在此添加控件通知处理程序代码
	UpdateData(TRUE);
	if (m_strPNo.IsEmpty() || m_strPName.IsEmpty())
	{
		AfxMessageBox("请输入相应数据！");
		CWnd *pWnd;
		pWnd = GetDlgItem(IDC_EDIT_PNo);
		pWnd->SetFocus();
		return;
	}
	if (m_bAdd)
	{
		m_rsProductSet.AddNew();
	}
	else
	{
		m_rsProductSet.Edit();
	}
	WriteRecord();
	m_rsProductSet.Update();
	m_rsProductSet.Requery();
	m_rsProductSet.MoveFirst();
	m_bFirst = true;
	m_bLast = false;
	m_bAdd = false;
	m_bEdit = false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CProductDlg::OnBnClickedBnCancel()
{
	// TODO: 在此添加控件通知处理程序代码
	m_bAdd = false;
	m_bEdit = false;
	ReadRecord();
	SetMoveBNState();
	SetEditState();
}


void CProductDlg::OnBnClickedBnExit()
{
	// TODO: 在此添加控件通知处理程序代码
	CDialog::OnOK();
}
