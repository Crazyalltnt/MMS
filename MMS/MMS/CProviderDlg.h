#pragma once
#include "ProviderSet.h"

// CProviderDlg 对话框

class CProviderDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CProviderDlg)

public:
	CProviderDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CProviderDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_PROVIDER };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strPVNo_Q;
	CString m_strPVNAME_Q;
	CString m_strPVNo;
	CString m_strPVName;
	CString m_strPVCon;
	CString m_strPVTel;
	CString m_strPVCode;
	CString m_strPVNam;
	CString m_strPVBank;
	CString m_strPVAcc;
	CProviderSet m_rsProviderSet;
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
