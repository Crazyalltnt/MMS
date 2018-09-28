// ProductSet.h : CProductSet 类的实现



// CProductSet 实现

// 代码生成在 2018年6月9日, 13:10

#include "stdafx.h"
#include "ProductSet.h"
IMPLEMENT_DYNAMIC(CProductSet, CRecordset)

CProductSet::CProductSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ProductID = "";
	m_ProductName = L"";
	m_ProductPrice = 0.0;
	m_Standard = "";
	m_Description = "";
	m_ProviderID = "";
	m_nFields = 6;
	m_nDefaultType = dynaset;
}
//#error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CProductSet::GetDefaultConnect()
{
	return _T("DSN=MMS;Description=Mall management system;UID=sa;PWD=61.134.54.18;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DESKTOP-MR0I0EL;DATABASE=MMS;Regional=Yes;");
}

CString CProductSet::GetDefaultSQL()
{
	return _T("[dbo].[Goods]");
}

void CProductSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[ProductID]"), m_ProductID);
	RFX_Text(pFX, _T("[ProductName]"), m_ProductName);
	RFX_Double(pFX, _T("[ProductPrice]"), m_ProductPrice);
	RFX_Text(pFX, _T("[Standard]"), m_Standard);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Text(pFX, _T("[ProviderID]"), m_ProviderID);

}
/////////////////////////////////////////////////////////////////////////////
// CProductSet 诊断

#ifdef _DEBUG
void CProductSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CProductSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


