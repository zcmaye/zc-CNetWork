#include"../CNetWork/CTcpSocket.h"
#include"../CNetWork/CTcpServer.h"
#include"../CNetWork/CHostAddress.h"
//#include<iostream>
//using namespace std;

int main()
{
	CTcpSocket client;
	//CHostAddress addr(CHostAddress::LocalHost);
	//cout << "Address:" << addr.toIpv4Address()<<" "<<addr.toString() << endl;

	//CHostAddress addr1(CHostAddress::AnyIPv4);
	//cout << "Address:" << addr1.toIpv4Address() << " " << addr1.toString() << endl;

	//CHostAddress addr2(CHostAddress::Null);
	//cout << "Address:" << addr2.toIpv4Address() << " " << addr2.toString() << endl;

	//CHostAddress addr3(CHostAddress::Boroadcast);
	//cout << "Address:" << addr3.toIpv4Address() << " " << addr3.toString() << endl;

	//CHostAddress null;
	//cout << "Address:" << null.toIpv4Address() << " " << null.toString() << endl;

	//CHostAddress sockAddr(123);
	//cout << "Address:" << sockAddr.toIpv4Address() << " " << sockAddr.toString() << endl;

	/*CHostAddress str("127.0.0.1");
	cout << "Address:" << str.toIpv4Address() << " " << str.toString() << endl;*/



	printf( "begin connecnt host\n" );
#ifndef C_WIN
	client.connectToHost(CHostAddress("127.0.0.1"), 8848);
#else
	client.connectToHost(CHostAddress("139.155.36.31"), 8848);
#endif // C_WIN

	
	//client.peerName();

	while (true)
	{

		/*while (client.canRead())
		{
			string buf = client.readAll();
			printf("recv:%s", buf.c_str());
		}*/
		printf(" ---- %s\n",client.read(1024).c_str());
	}

	


	getchar();
	getchar();
	return 0;
}