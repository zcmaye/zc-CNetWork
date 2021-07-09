#include "CTcpSocket.h"
#include"CSystemSocket.h"
#include<thread>
#include<string.h>

#ifdef C_WIN
#define log(errMsg) printf("[%s] failed,error code %d\n",errMsg,WSAGetLastError())
#else
#define log(errMsg) printf("[%s] failed,error code %d\n",errMsg,errno)
#endif

/*@Tcp*/
CTcpSocket::CTcpSocket():fd(~0)
{
	CSystemSocket::initSocket();
	
}

CTcpSocket::CTcpSocket(fd_t fd)
{
	this->fd = fd;
	//检测套接字是否可读，实现异步读取
	auto func = [=]()
	{
		while (true)
		{
			print("thread %s\n", isCanRead ? "true" : "false");
			char buf[128] = { 0 };
			if (0 < recv(fd, buf, sizeof(buf), MSG_PEEK))
			{
				isCanRead = true;
			}
			else
			{
				break;
			}
		}
	};
	pthread = new std::thread(func);
}

CTcpSocket::~CTcpSocket()
{
	CSystemSocket::closeSocket();
}

void CTcpSocket::connectToHost(const CHostAddress& address, cuint16 port, CTcp::NetworkProtocol protocol)
{
	fd =CSystemSocket::socket(protocol, SOCK_STREAM, IPPROTO_TCP);
	if (fd == INVALID_SOCKET)
	{
		log("socket");
	}
	sockaddr_in serAddr;
	serAddr.sin_family = protocol;
	serAddr.sin_port = htons(port);
	serAddr.sin_addr.s_addr = address.toIpv4Address();

	if (CSystemSocket::connect(fd, (sockaddr*)&serAddr, sizeof(sockaddr_in)) == SOCKET_ERROR)
	{
		log("connect");
	}
	//检测套接字是否可读，实现异步读取
	auto func = [=]()
	{
		while (true)
		{
			print("thread %s\n", isCanRead ? "true" : "false");
			char buf[128] = { 0 };
			if (0 < recv(fd, buf, sizeof(buf), MSG_PEEK))
			{
				isCanRead = true;
			}
			else
			{
				break;
			}
		}
	};
	pthread = new std::thread(func);
}

bool CTcpSocket::canRead()
{

	return isCanRead;
}

cuint64 CTcpSocket::read(char* data, cuint64 maxSize)
{
	isCanRead = false;
	return CSystemSocket::recv(fd, data, maxSize, 0);
}

string CTcpSocket::read(cuint64 maxSize)
{
	char* buf = new char[maxSize+1] {0};
	CSystemSocket::recv(fd, buf, maxSize, 0);
	string result(buf);
	delete buf;
	isCanRead = false;
	return std::move(result);
}
string CTcpSocket::readAll()
{	
	char buf[1024] = {0};
	string result;
	while (1)
	{
		isCanRead = false;
		CSystemSocket::recv(fd, buf, 1024, 0);
		result.append(buf);
		memset(buf, 0, sizeof(buf));
		if (!this->canRead())
		{
			break;
		}
		if (result.size() >= 100 * 1024)
		{
			return std::move(result);
		}
	}
	isCanRead = false;
	return std::move(result);
}

cuint64 CTcpSocket::write(const char* data, cuint64 maxSize)
{
	return CSystemSocket::send(fd,data,maxSize,0);
}

cuint64 CTcpSocket::write(const char* data)
{
	return CSystemSocket::send(fd, data, strlen(data), 0);
}

cuint64 CTcpSocket::write(const string& data)
{
	return write(data.c_str());
}

CTcp::SockAddr CTcpSocket::peerAddress() const
{
	
	return CTcp::SockAddr();
}

std::string CTcpSocket::peerName() const
{
	sockaddr_in addr;
	int len = sizeof(sockaddr_in);
#ifdef C_WIN
	getpeername(fd, (sockaddr*)&addr, &len);
#else
	getpeername(fd, (sockaddr*)&addr, (socklen_t*)&len);
#endif // C_WIN
	char str[INET_ADDRSTRLEN] = "";
	inet_ntop(AF_INET, &addr.sin_addr, str, INET_ADDRSTRLEN);

	return std::string(str);
}

cuint16 CTcpSocket::peerPort() const
{
	return cuint16();
}

