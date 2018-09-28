// StockSet.h : CStockSet 类的实现



// CStockSet 实现

// 代码生成在 2018年6月9日, 22:31

#include "stdafx.h"
#include "StockSet.h"
IMPLEMENT_DYNAMIC(CStockSet, CRecordset)

CStockSet::CStockSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ProductID = "";
	m_StockDate;
	m_StockQuantity = 0.0;
	m_StockPrice = 0.0;
	m_Inventory = 0.0;
	m_ProviderID = "";
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
//#error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CStockSet::GetDefaultConnect()
{
	return _T("DSN=MMS;Description=Mall management system;UID=sa;PWD=61.134.54.18;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DESKTOP-MR0I0EL;DATABASE=MMS;Regional=Yes;");
}

CString CStockSet::GetDefaultSQL()
{
	return _T("[dbo].[Stock]");
}

void CStockSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[ProductID]"), m_ProductID);
	RFX_Date(pFX, _T("[StockDate]"), m_StockDate);
	RFX_Double(pFX, _T("[StockQuantity]"), m_StockQuantity);
	RFX_Double(pFX, _T("[StockPrice]"), m_StockPrice);
	RFX_Double(pFX, _T("[Inventory]"), m_Inventory);
	RFX_Text(pFX, _T("[ProviderID]"), m_ProviderID);

}
/////////////////////////////////////////////////////////////////////////////
// CStockSet 诊断

#ifdef _DEBUG
void CStockSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CStockSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


