#pragma once
#include "StockSet.h"

// CStockDlg 对话框

class CStockDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CStockDlg)

public:
	CStockDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CStockDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_STOCK };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strSTNo_Q;
	CString m_strSTNo;
	double m_strSTPrice;
	double m_strSTNum;
	CString m_strSTPRNo;
	double m_strSTInv;
	CString m_strSTDate;
	CStockSet m_rsStockSet;
	bool m_bEmpty;
	bool m_bFirst;
	bool m_bLast;
	bool m_bAdd;
	bool m_bEdit;
	void ClearEditData(void);
	void ReadRecord(void);
	void WriteRecord(void);
	void SetMoveBNState(void);
	void SetEditState(void);
	virtual BOOL OnInitDialog();
	afx_msg void OnBnClickedBnFirst();
	afx_msg void OnBnClickedBnPrev();
	afx_msg void OnBnClickedBnNext();
	afx_msg void OnBnClickedBnLast();
	afx_msg void OnBnClickedBnAdd();
	afx_msg void OnBnClickedBnQuery();
	afx_msg void OnBnClickedBnEdit();
	afx_msg void OnBnClickedBnDelete();
	afx_msg void OnBnClickedBnSave();
	afx_msg void OnBnClickedBnCancel();
	afx_msg void OnBnClickedBnExit();
};
