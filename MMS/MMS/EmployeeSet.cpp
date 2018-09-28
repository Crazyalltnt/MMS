// EmployeeSet.h : CEmployeeSet ���ʵ��



// CEmployeeSet ʵ��

// ���������� 2018��6��10��, 16:18

#include "stdafx.h"
#include "EmployeeSet.h"
IMPLEMENT_DYNAMIC(CEmployeeSet, CRecordset)

CEmployeeSet::CEmployeeSet(CDatabase* pdb)
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
CString CEmployeeSet::GetDefaultConnect()
{
	return _T("DSN=MMS;Description=Mall management system;UID=sa;PWD=61.134.54.18;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DESKTOP-MR0I0EL;DATABASE=MMS;Regional=Yes;");
}

CString CEmployeeSet::GetDefaultSQL()
{
	return _T("[dbo].[Employee]");
}

void CEmployeeSet::DoFieldExchange(CFieldExchange* pFX)
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
// CEmployeeSet ���

#ifdef _DEBUG
void CEmployeeSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CEmployeeSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


