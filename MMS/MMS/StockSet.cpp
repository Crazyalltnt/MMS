// StockSet.h : CStockSet ���ʵ��



// CStockSet ʵ��

// ���������� 2018��6��9��, 22:31

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
//#error ��ȫ����: �����ַ������ܰ������롣
// �������ַ����п��ܰ������������/��������Ҫ
// ��Ϣ�����ڲ鿴��������ַ������ҵ������밲ȫ
// �йص�������Ƴ� #error��������Ҫ���������
// ��Ϊ������ʽ��ʹ���������û������֤��
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
// RFX_Text() �� RFX_Int() �������������
// ��Ա���������ͣ����������ݿ��ֶε����͡�
// ODBC �����Զ�����ֵת��Ϊ�����������
	RFX_Text(pFX, _T("[ProductID]"), m_ProductID);
	RFX_Date(pFX, _T("[StockDate]"), m_StockDate);
	RFX_Double(pFX, _T("[StockQuantity]"), m_StockQuantity);
	RFX_Double(pFX, _T("[StockPrice]"), m_StockPrice);
	RFX_Double(pFX, _T("[Inventory]"), m_Inventory);
	RFX_Text(pFX, _T("[ProviderID]"), m_ProviderID);

}
/////////////////////////////////////////////////////////////////////////////
// CStockSet ���

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


