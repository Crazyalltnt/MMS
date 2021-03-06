#pragma once
#include "ProductSet.h"

// CProductDlg 对话框

class CProductDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProductDlg)

public:
	CProductDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CProductDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PRODUCT };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	virtual BOOL OnInitDialog();
	CString m_strPNo_Q;
	CString m_strPNAME_Q;
	CString m_strPNo;
	CString m_strPName;
	double m_strPPrice;
	CString m_strPStd;
	CString m_strPDes;
	CString m_strPRNo;
	CProductSet m_rsProductSet;
	void ClearEditData(void);
	void ReadRecord(void);
	void WriteRecord(void);
	void SetMoveBNState(void);
	void SetEditState(void);
	bool m_bEmpty;
	bool m_bAdd;
	bool m_bFirst;
	bool m_bLast;
	bool m_bEdit;
	afx_msg void OnBnClickedBnAdd();
	afx_msg void OnBnClickedBnFirst();
	afx_msg void OnBnClickedBnLast();
	afx_msg void OnBnClickedBnQuery();
	afx_msg void OnBnClickedBnPrev();
	afx_msg void OnBnClickedBnNext();
	afx_msg void OnBnClickedBnEdit();
	afx_msg void OnBnClickedBnDelete();
	afx_msg void OnBnClickedBnSave();
	afx_msg void OnBnClickedBnCancel();
	afx_msg void OnBnClickedBnExit();
};
