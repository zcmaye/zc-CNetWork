#include"CSystemSocket.h"

//
//void CTcpSocket::connectToHost(const CHostAddress& address, cuint16 port, CTcp::NetworkProtocol protocol)
//{
//	fd = socket(protocol, SOCK_STREAM, IPPROTO_TCP);
//	if (fd == INVALID_SOCKET)
//	{
//		log("socket");
//	}
//	sockaddr_in serAddr;
//	serAddr.sin_family = protocol;
//	serAddr.sin_port = htons(port);
//	serAddr.sin_addr.S_un.S_addr = address.toIpv4Address();
//
//	if (connect(fd, (sockaddr*)&serAddr, sizeof(sockaddr_in)) == SOCKET_ERROR)
//	{
//		log("connect");
//	}
//}
//
//int CTcpSocket::sendMsg(const char* str)
//{
//	int len = send(fd, str, strlen(str), 0);
//	if (len == SOCKET_ERROR)
//	{
//		log("send");
//	}
//	return len;
//}
//
//int CTcpSocket::sendMsg(const std::string str)
//{
//	return sendMsg(str.c_str());
//}
//
//int CTcpSocket::recvMsg(char* buf, int len)
//{
//	int ret = recv(fd, buf, len, 0);
//	if (ret == SOCKET_ERROR)
//	{
//		log("recv");
//	}
//	return ret;
//}


bool CSystemSocket::initSocket()
{
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		print("WSAStartup");
	}
	return false;
}

bool CSystemSocket::closeSocket()
{
	if (WSACleanup() != 0)
	{
		print("WSACleanup");
	}
	return false;
}

fd_t CSystemSocket::socket(int af, int type, int protocol)
{	
	return ::socket(af, type, protocol);
}

int CSystemSocket::bind(fd_t fd, const sockaddr* name, int namelen)
{
	return ::bind(fd,name,namelen);
}

int CSystemSocket::listen(fd_t fd, int backlog)
{
	return ::listen(fd,backlog);
}

int CSystemSocket::connect(fd_t fd, const sockaddr* name, int namelen)
{
	return ::connect(fd,name, namelen);
}

fd_t CSystemSocket::accept(fd_t fd, sockaddr* addr, int* addrlen)
{
	return ::accept(fd, addr,addrlen);
}

cuint64 CSystemSocket::recv(fd_t fd, char* buf, cuint64 len, int flags)
{
	return ::recv(fd,buf,len,flags);
}

cuint64 CSystemSocket::send(fd_t fd, const char* buf, cuint64 len, int flags)
{
	return ::send(fd, buf, len, flags);
}
