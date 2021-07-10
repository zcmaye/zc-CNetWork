#include"../CNetWork/CTcpServer.h"
#include"../CNetWork/CTcpSocket.h"
#include"../CNetWork/CHostAddress.h"
#include<vector>
#include<stdlib.h>
int main()
{
	/*
	 g++ main.cpp ../CNetWork/CTcpServer.cpp ../CNetWork/CTcpSocket.cpp ../CNetWork/CSystemSocket.cpp ../CNetWork/CHostAddress.cpp -o client -lpthread
	*/
	std::vector<CTcpSocket*> fds;
	CTcpServer server;
	server.listen(CHostAddress::AnyIPv4, 8848);
	print("wait client connect...\n");
	while (true)
	{
		CTcpSocket* tcpSocket = server.waitNewConnent();
		if (tcpSocket == nullptr)
		{
			print("tcpSocket is nullptr，正在等待重新连接\n");
			continue;
		}
		else
		{
			print("tcpSocket create succed... %d\n",fds.size());
			fds.push_back(tcpSocket);
		}
		for(int i=0;i<5;i++)
		{
			for (auto& tcp : fds)
			{
				if (SOCKET_ERROR == tcp->write("Helo I'm maye"))
				{
					auto delIt = std::find(fds.begin(), fds.end(), tcp);
					if (delIt != fds.end())
					{
						fds.erase(delIt);
						print("tcpSocket remove succed\n");
					}
				}
			}
			//sleep(100);
		}
	}



	getchar();
	getchar();
	return 0;
}