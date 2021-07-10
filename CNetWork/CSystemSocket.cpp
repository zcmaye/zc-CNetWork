#include"CSystemSocket.h"

bool CSystemSocket::initSocket()
{
#ifdef  C_WIN
	WSADATA wsadata;
	if (WSAStartup(MAKEWORD(2, 2), &wsadata) != 0)
	{
		print("WSAStartup");
		return false;
	}
#endif //  C_WIN
	return true;
}

bool CSystemSocket::closeSocket()
{
#ifdef C_WIN
	if (WSACleanup() != 0)
	{
		print("WSACleanup");
		return false;
	}
#endif
	return true;
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

fd_t CSystemSocket::accept(fd_t fd, sockaddr* addr, socklen_t* addrlen)
{
#ifdef C_WIN
	return ::accept(fd, addr,(int*)addrlen);
#else
	return ::accept(fd, addr, addrlen);
#endif
}

cuint64 CSystemSocket::recv(fd_t fd, char* buf, cuint64 len, int flags)
{
	return ::recv(fd,buf,len,flags);
}

cuint64 CSystemSocket::send(fd_t fd, const char* buf, cuint64 len, int flags)
{
	return ::send(fd, buf, len, flags);
}
