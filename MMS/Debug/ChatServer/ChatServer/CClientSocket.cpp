// CClientSocket.cpp: 实现文件
//

#include "stdafx.h"
#include "ChatServer.h"
#include "CClientSocket.h"
#include "ChatServerDlg.h"


// CClientSocket

CClientSocket::CClientSocket()
{
}

CClientSocket::~CClientSocket()
{
}


// CClientSocket 成员函数

void CClientSocket::OnReceive(int nErrorCode)
{
	// TODO: 在此添加专用代码和/或调用基类
	CChatServerDlg* dlg = (CChatServerDlg*)AfxGetApp()->GetMainWnd();
	//获取时间 
	dlg->m_tm = CTime::GetCurrentTime();
	CString str;
	str = dlg->m_tm.Format("%X ");
	//接收数据 
	Receive(dlg->buff, 200, 0);
	CString temp1 = dlg->buff;
	//解码，收到的数据 
	int index = 0;
	for (int i = 0; i<3; i++)
	{
		index = temp1.Find('#', index);
		index++;
	}
	int sum = temp1.GetLength();
	int count = sum - index;
	CString message = temp1.Mid(index, count);
	CString temp2 = " 客户端 : ";
	temp2 = str + temp2;
	temp2 += message;
	dlg->m_list.AddString(temp2);

	CAsyncSocket::OnReceive(nErrorCode);
}