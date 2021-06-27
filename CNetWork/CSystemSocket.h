#pragma once
#include"Cglobal.h"
#include<ws2tcpip.h>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

#ifdef _WIN32
using fd_t = SOCKET;
#else
//LINUX
#endif // _WIN32

class CSystemSocket
{

public:
	static bool initSocket();
	static bool closeSocket();
	static fd_t socket(int af, int type, int protocol);
	static int bind(fd_t fd, const struct sockaddr * name, int namelen);
	static int listen(fd_t fd, int backlog);
	static int connect(fd_t fd, const struct sockaddr* name, int namelen);
	static fd_t accept(fd_t fd,struct sockaddr * addr,int * addrlen);
	static cuint64 recv(fd_t fd, char* buf, cuint64 len, int flags);
	static cuint64 send(fd_t fd, const char* buf, cuint64 len, int flags);
private:

};