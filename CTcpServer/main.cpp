#include"../CNetWork/CTcpServer.h"
#include"../CNetWork/CTcpSocket.h"
#include"../CNetWork/CHostAddress.h"
#include<vector>
int main()
{
	std::vector<CTcpSocket*> fds;
	CTcpServer server;
	server.listen(CHostAddress("127.0.0.1"), 8888);
	CTcpSocket *tcpSocket =  server.waitNewConnent();
	if (tcpSocket == nullptr)
		return -2;
	else
	{
		fds.push_back(tcpSocket);
	}
	print("客户端连接成功~\n");
	while (true)
	{
		for (auto& tcp : fds)
		{
			tcp->write("Helo I'm maye");
		}
		printf("send msg %d\n",fds.size());
		Sleep(100);
	}


	getchar();
	getchar();
	return 0;
}