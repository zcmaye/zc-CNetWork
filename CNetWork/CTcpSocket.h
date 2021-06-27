#pragma once
#include"CHostAddress.h"
namespace std
{
	class thread;
}


namespace CTcp
{
	enum SockAddr
	{
		Addr_Any = 0x000000,
		Addr_LoaclHost = 0x100007F
	};
	/*@网络协议类型*/
	enum NetworkProtocol
	{
		IPv4Protocol =2,
		IPv6Protocol = 23
	};
}

/*@Tcp*/
class CTcpSocket
{
	using fd_t = unsigned int;		//描述符
public:
	CTcpSocket();
	CTcpSocket(fd_t fd);	//把系统原生socket转成CTcpSocket
	~CTcpSocket();
	void connectToHost(const CHostAddress& address, cuint16 port, CTcp::NetworkProtocol protocol= CTcp::IPv4Protocol);
	bool canRead();

	//read And Write
	cuint64 read(char* data, cuint64 maxSize);
	string read(cuint64 maxSize);
	string readAll();				//此函数有问题
	cuint64 write(const char* data, cuint64 masSize);
	cuint64 write(const char* data);
	cuint64 write(const string& data);


	CTcp::SockAddr	peerAddress() const;
	std::string		peerName() const;
	cuint16			peerPort() const;

	inline fd_t getFd() { return fd; }
private:
	fd_t fd;
	std::thread* pthread;
	bool isCanRead = false;
};

