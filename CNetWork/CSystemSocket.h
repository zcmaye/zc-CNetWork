#pragma once
#include"Cglobal.h"

#ifdef C_WIN
#include<ws2tcpip.h>
#include<WinSock2.h>
#pragma comment(lib,"ws2_32.lib")

using fd_t = SOCKET;
#else	
#include<sys/socket.h>
#include<sys/types.h>
#include<netinet/in.h>
#include<arpa/inet.h>

using fd_t = int;
#define INVALID_SOCKET          (-1)
#define SOCKET_ERROR            (-1)


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
	static fd_t accept(fd_t fd,struct sockaddr * addr, socklen_t* addrlen);
	static cuint64 recv(fd_t fd, char* buf, cuint64 len, int flags);
	static cuint64 send(fd_t fd, const char* buf, cuint64 len, int flags);
private:

};