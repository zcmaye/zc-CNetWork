#include"../CNetWork/CTcpServer.h"
#include"../CNetWork/CTcpSocket.h"
#include"../CNetWork/CHostAddress.h"
#include<vector>
#include<stdlib.h>
int main()
{
	std::vector<CTcpSocket*> fds;
	CTcpServer server;
	server.listen(CHostAddress::AnyIPv4, 8848);
	print("wait client connect...\n");
	while (true)
	{
		CTcpSocket* tcpSocket = server.waitNewConnent();
		if (tcpSocket == nullptr)
			continue;
		else
		{
			fds.push_back(tcpSocket);
		}
		print("客户端连接成功~\n");
		for(int i=0;i<5;i++)
		{
			for (auto& tcp : fds)
			{
				tcp->write("Helo I'm maye");
			}
			printf("send msg %lu\n", fds.size());
			//sleep(100);
		}
	}



	getchar();
	getchar();
	return 0;
}