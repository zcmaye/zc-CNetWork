#pragma once
#include"CSystemSocket.h"
#include"CHostAddress.h"

class CTcpSocket;

class CTcpServer
{
	using fd_t = unsigned int;		//ÃèÊö·û
public:
	CTcpServer();
	~CTcpServer();
	bool listen(const CHostAddress& address = CHostAddress::AnyIPv4, cuint16 port = 8888);
	CTcpSocket* waitNewConnent();
private:
	fd_t fd;
};

