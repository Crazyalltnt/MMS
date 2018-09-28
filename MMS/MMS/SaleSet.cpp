// SaleSet.h : CSaleSet ���ʵ��



// CSaleSet ʵ��

// ���������� 2018��6��10��, 10:16

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
//#error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
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
// CSaleSet ���

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


