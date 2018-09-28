// ClientSet.h : CClientSet 类的实现



// CClientSet 实现

// 代码生成在 2018年6月10日, 15:09

#include "stdafx.h"
#include "ClientSet.h"
IMPLEMENT_DYNAMIC(CClientSet, CRecordset)

CClientSet::CClientSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ClientID = "";
	m_Address = "";
	m_ZipCode = "";
	m_Contacts = "";
	m_Telephone = "";
	m_nFields = 5;
	m_nDefaultType = dynaset;
}
//#error 安全问题: 连接字符串可能包含密码。
// 此连接字符串中可能包含明文密码和/或其他重要
// 信息。请在查看完此连接字符串并找到所有与安全
// 有关的问题后移除 #error。可能需要将此密码存
// 储为其他格式或使用其他的用户身份验证。
CString CClientSet::GetDefaultConnect()
{
	return _T("DSN=MMS;Description=Mall management system;UID=sa;PWD=61.134.54.18;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DESKTOP-MR0I0EL;DATABASE=MMS;Regional=Yes;");
}

CString CClientSet::GetDefaultSQL()
{
	return _T("[dbo].[Client]");
}

void CClientSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() 和 RFX_Int() 这类宏依赖的是
// 成员变量的类型，而不是数据库字段的类型。
// ODBC 尝试自动将列值转换为所请求的类型
	RFX_Text(pFX, _T("[ClientID]"), m_ClientID);
	RFX_Text(pFX, _T("[Address]"), m_Address);
	RFX_Text(pFX, _T("[ZipCode]"), m_ZipCode);
	RFX_Text(pFX, _T("[Contacts]"), m_Contacts);
	RFX_Text(pFX, _T("[Telephone]"), m_Telephone);

}
/////////////////////////////////////////////////////////////////////////////
// CClientSet 诊断

#ifdef _DEBUG
void CClientSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CClientSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


