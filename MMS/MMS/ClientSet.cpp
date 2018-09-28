// ClientSet.h : CClientSet ���ʵ��



// CClientSet ʵ��

// ���������� 2018��6��10��, 15:09

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
//#error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[ClientID]"), m_ClientID);
	RFX_Text(pFX, _T("[Address]"), m_Address);
	RFX_Text(pFX, _T("[ZipCode]"), m_ZipCode);
	RFX_Text(pFX, _T("[Contacts]"), m_Contacts);
	RFX_Text(pFX, _T("[Telephone]"), m_Telephone);

}
/////////////////////////////////////////////////////////////////////////////
// CClientSet ���

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


