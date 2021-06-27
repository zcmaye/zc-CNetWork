#include "CHostAddress.h"
#include<WS2tcpip.h>

CHostAddress::CHostAddress(const string& address) :CHostAddress()
{
	in_addr addr = { 0 };
	if (1 != inet_pton(AF_INET, address.c_str(), &addr))
	{
		print("[CHostAddress line %d]:地址转换失败\n", __LINE__);
		this->address = 0;
	}
	this->address = addr.S_un.S_addr;
}

CHostAddress::CHostAddress(const CHostAddress& address) :CHostAddress()
{
	*this = address;
}

CHostAddress::CHostAddress(const sockaddr* sockaddr) :CHostAddress()
{
	this->address = ((sockaddr_in*)sockaddr)->sin_addr.S_un.S_addr;
}

CHostAddress::CHostAddress(cuint32 ipv4addr):CHostAddress()
{
	this->address = ipv4addr;
}

CHostAddress::CHostAddress(CHostAddress::SpecialAddress address):CHostAddress()
{
	switch (address)
	{
	case CHostAddress::Null:
		this->addressString = "Null";
		break;
	case CHostAddress::Boroadcast:
		this->addressString = "255.255.255.255";
		break;
	case CHostAddress::LocalHost:
		this->addressString = "127.0.0.1";
		break;
	case CHostAddress::AnyIPv4:
		this->addressString = "0.0.0.0";
		break;
	}
	*this = CHostAddress(this->addressString);
}

CHostAddress::CHostAddress()
{
	this->address = 0;
	this->addressString = "Null";
}

CHostAddress::~CHostAddress()
{
}

cuint32 CHostAddress::toIpv4Address() const
{
	return address;
}

string CHostAddress::toString() const 
{
	//如果ip地址是Null,尝试把address转换一下
	if (addressString == "Null")
	{
		char buf[50] = { 0 };
		if (inet_ntop(AF_INET, &address, buf, 50)!=nullptr)
		{
			addressString = buf;
		}
	}
	return addressString;
}


bool CHostAddress::operator!=(const CHostAddress& other) const
{
	return this->address != other.address;
}

bool CHostAddress::operator!=(CHostAddress::SpecialAddress other) const
{
	return this->address != CHostAddress(other).address;
}

bool CHostAddress::operator==(const CHostAddress& other) const
{
	return this->address == other.address;
}

bool CHostAddress::operator==(CHostAddress::SpecialAddress other) const
{
	return this->address == CHostAddress(other).address;
}
