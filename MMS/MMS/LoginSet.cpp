// LoginSet.h : CLoginSet 类的实现



// CLoginSet 实现

// 代码生成在 2018年6月10日, 21:53

#include "stdafx.h"
#include "LoginSet.h"
IMPLEMENT_DYNAMIC(CLoginSet, CRecordset)

CLoginSet::CLoginSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_EmployeeID = "";
	m_EmployeeName = "";
	m_Authority = "";
	m_Password = "";
	m_nFields = 4;
	m_nDefaultType = dynaset;
}
//#error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CLoginSet::GetDefaultConnect()
{
	return _T("DSN=MMS;Description=Mall management system;UID=sa;PWD=61.134.54.18;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DESKTOP-MR0I0EL;DATABASE=MMS;Regional=Yes;");
}

CString CLoginSet::GetDefaultSQL()
{
	return _T("[dbo].[Employee]");
}

void CLoginSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[EmployeeID]"), m_EmployeeID);
	RFX_Text(pFX, _T("[EmployeeName]"), m_EmployeeName);
	RFX_Text(pFX, _T("[Authority]"), m_Authority);
	RFX_Text(pFX, _T("[Password]"), m_Password);

}
/////////////////////////////////////////////////////////////////////////////
// CLoginSet 诊断

#ifdef _DEBUG
void CLoginSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CLoginSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


