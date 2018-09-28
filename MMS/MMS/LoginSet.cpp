// LoginSet.h : CLoginSet ���ʵ��



// CLoginSet ʵ��

// ���������� 2018��6��10��, 21:53

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
//#error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[EmployeeID]"), m_EmployeeID);
	RFX_Text(pFX, _T("[EmployeeName]"), m_EmployeeName);
	RFX_Text(pFX, _T("[Authority]"), m_Authority);
	RFX_Text(pFX, _T("[Password]"), m_Password);

}
/////////////////////////////////////////////////////////////////////////////
// CLoginSet ���

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


