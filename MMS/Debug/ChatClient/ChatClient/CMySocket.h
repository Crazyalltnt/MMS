#pragma once

// CMySocket 命令目标

class CMySocket : public CAsyncSocket
{
public:
	CMySocket();
	virtual ~CMySocket();
	virtual void OnConnect(int nErrorCode);
	virtual void OnReceive(int nErrorCode);
};


