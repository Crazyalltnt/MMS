#pragma once
#include "EmployeeSet.h"

// CEmployeeDlg 对话框

class CEmployeeDlg : public CDialogEx
{
	DECLARE_DYNAMIC(CEmployeeDlg)

public:
	CEmployeeDlg(CWnd* pParent = nullptr);   // 标准构造函数
	virtual ~CEmployeeDlg();

// 对话框数据
#ifdef AFX_DESIGN_TIME
	enum { IDD = IDD_DIALOG_EMPLOYEE };
#endif

protected:
	virtual void DoDataExchange(CDataExchange* pDX);    // DDX/DDV 支持
	afx_msg void OnPaint();
	DECLARE_MESSAGE_MAP()
public:
	CString m_strENo_Q;
	CString m_strENAME_Q;
	CString m_strENo;
	CString m_strEName;
	CString m_strEAu;
	CString m_strEPass;
	CEmployeeSet m_rsEmployeeSet;
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
