// CServerSocket.cpp: 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "CServerSocket.h"
#include "ChatServerDlg.h"


// CServerSocket

CServerSocket::CServerSocket()
{
}

CServerSocket::~CServerSocket()
{
}


// CServerSocket 成员函数

void CServerSocket::OnAccept(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CChatServerDlg* dlg = (CChatServerDlg*)AfxGetApp()->GetMainWnd();
	dlg->m_client = new CClientSocket;
	Accept(*(dlg->m_client));
	CString str;
	dlg->m_tm = CTime::GetCurrentTime();
	str = dlg->m_tm.Format("%X ");
	str += "客户端连接成功!";
	dlg->m_list.AddString(str);
	dlg->m_list.UpdateData(FALSE);

	CAsyncSocket::OnAccept(nErrorCode);
}