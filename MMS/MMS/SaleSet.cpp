// SaleSet.h : CSaleSet 类的实现



// CSaleSet 实现

// 代码生成在 2018年6月10日, 10:16

#include "stdafx.h"
#include "SaleSet.h"
IMPLEMENT_DYNAMIC(CSaleSet, CRecordset)

CSaleSet::CSaleSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_SaleID = "";
	m_ProductID = "";
	m_SaleDate;
	m_SalePrice = 0.0;
	m_SaleQuantity = 0.0;
	m_ClientID = "";
	m_Discount = 0;
	m_EmployeeID = "";
	m_nFields = 8;
	m_nDefaultType = dynaset;
}
//#error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CSaleSet::GetDefaultConnect()
{
	return _T("DSN=MMS;Description=Mall management system;UID=sa;PWD=61.134.54.18;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DESKTOP-MR0I0EL;DATABASE=MMS;Regional=Yes;");
}

CString CSaleSet::GetDefaultSQL()
{
	return _T("[dbo].[Sale]");
}

void CSaleSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[SaleID]"), m_SaleID);
	RFX_Text(pFX, _T("[ProductID]"), m_ProductID);
	RFX_Date(pFX, _T("[SaleDate]"), m_SaleDate);
	RFX_Double(pFX, _T("[SalePrice]"), m_SalePrice);
	RFX_Double(pFX, _T("[SaleQuantity]"), m_SaleQuantity);
	RFX_Text(pFX, _T("[ClientID]"), m_ClientID);
	RFX_Double(pFX, _T("[Discount]"), m_Discount);
	RFX_Text(pFX, _T("[EmployeeID]"), m_EmployeeID);

}
/////////////////////////////////////////////////////////////////////////////
// CSaleSet 诊断

#ifdef _DEBUG
void CSaleSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CSaleSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


