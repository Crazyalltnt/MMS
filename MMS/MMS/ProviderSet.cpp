// ProviderSet.h : CProviderSet ���ʵ��



// CProviderSet ʵ��

// ���������� 2018��6��9��, 16:19

#include "stdafx.h"
#include "ProviderSet.h"
IMPLEMENT_DYNAMIC(CProviderSet, CRecordset)

CProviderSet::CProviderSet(CDatabase* pdb)
	: CRecordset(pdb)
{
	m_ProviderID = "";
	m_ProviderName = "";
	m_ZipCode = "";
	m_Contacts = "";
	m_Telephone = "";
	m_Account = "";
	m_Bank = "";
	m_Holder = "";
	m_nFields = 8;
	m_nDefaultType = dynaset;
}
//#error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
CString CProviderSet::GetDefaultConnect()
{
	return _T("DSN=MMS;Description=Mall management system;UID=sa;PWD=61.134.54.18;APP=Microsoft\x00ae Visual Studio\x00ae;WSID=DESKTOP-MR0I0EL;DATABASE=MMS;Regional=Yes;");
}

CString CProviderSet::GetDefaultSQL()
{
	return _T("[dbo].[Provider]");
}

void CProviderSet::DoFieldExchange(CFieldExchange* pFX)
{
	pFX->SetFieldType(CFieldExchange::outputColumn);
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[ProviderID]"), m_ProviderID);
	RFX_Text(pFX, _T("[ProviderName]"), m_ProviderName);
	RFX_Text(pFX, _T("[ZipCode]"), m_ZipCode);
	RFX_Text(pFX, _T("[Contacts]"), m_Contacts);
	RFX_Text(pFX, _T("[Telephone]"), m_Telephone);
	RFX_Text(pFX, _T("[Account]"), m_Account);
	RFX_Text(pFX, _T("[Bank]"), m_Bank);
	RFX_Text(pFX, _T("[Holder]"), m_Holder);

}
/////////////////////////////////////////////////////////////////////////////
// CProviderSet ���

#ifdef _DEBUG
void CProviderSet::AssertValid() const
{
	CRecordset::AssertValid();
}

void CProviderSet::Dump(CDumpContext& dc) const
{
	CRecordset::Dump(dc);
}
#endif //_DEBUG


