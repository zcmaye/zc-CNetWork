#include "CTcpServer.h"
#include"CTcpSocket.h"

CTcpServer::CTcpServer() :fd(-1)
{
	CSystemSocket::initSocket();
}

CTcpServer::~CTcpServer()
{
	CSystemSocket::closeSocket();
}

bool CTcpServer::listen(const CHostAddress& address, cuint16 port)
{
	fd = CSystemSocket::socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET)
	{
		print("CSystemSocket::socket error\n");
		return false;
	}

	sockaddr_in addr;
	addr.sin_family = AF_INET;
	addr.sin_port = htons(port);
	addr.sin_addr.S_un.S_addr = address.toIpv4Address();
	if (SOCKET_ERROR == CSystemSocket::bind(fd, (sockaddr*)&addr, sizeof(sockaddr)))
	{
		print("CSystemSocket::bind error\n");
		return false;
	}

	CSystemSocket::listen(fd, 10);
	return true;
}

CTcpSocket* CTcpServer::waitNewConnent()
{
	static fd_set set;
	FD_ZERO(&set);
	FD_SET(fd, &set);

	fd_set readFds = set;
	select(1, &readFds, NULL, NULL, 0);
	if (FD_ISSET(fd, &readFds))
	{
		fd_t clifd = CSystemSocket::accept(fd, NULL, NULL);
		CTcpSocket* tcpSocket = new CTcpSocket(clifd);
		return tcpSocket;
	}

	return nullptr;
}
