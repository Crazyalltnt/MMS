#pragma once
#include "SaleSet.h"

// CSaleDlg 对话框

class CSaleDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CSaleDlg)

public:
	CSaleDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CSaleDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_SALE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strSAID_Q;
	CString m_strSANo_Q;
	CString m_strSAid;
	CString m_strSANo;
	double m_strSAPrice;
	CString m_strSADate;
	double m_strSANum;
	double m_strSADis;
	CString m_strSACid;
	CString m_strSAEid;
	CSaleSet m_rsSaleSet;
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
	afx_msg void OnBnClickedBnQuery();
	afx_msg void OnBnClickedBnAdd();
	afx_msg void OnBnClickedBnEdit();
	afx_msg void OnBnClickedBnDelete();
	afx_msg void OnBnClickedBnSave();
	afx_msg void OnBnClickedBnCancel();
	afx_msg void OnBnClickedBnExit();
};
