// ProductSet.h : CProductSet ���ʵ��



// CProductSet ʵ��

// ���������� 2018��6��9��, 13:10

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
//#error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[ProductID]"), m_ProductID);
	RFX_Text(pFX, _T("[ProductName]"), m_ProductName);
	RFX_Double(pFX, _T("[ProductPrice]"), m_ProductPrice);
	RFX_Text(pFX, _T("[Standard]"), m_Standard);
	RFX_Text(pFX, _T("[Description]"), m_Description);
	RFX_Text(pFX, _T("[ProviderID]"), m_ProviderID);

}
/////////////////////////////////////////////////////////////////////////////
// CProductSet ���

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


