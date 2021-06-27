#pragma once

#include"Cglobal.h"
#include<string>
using std::string;
//ÌáÇ°ÉùÃ÷
struct sockaddr;	

class CHostAddress
{
public:
	enum SpecialAddress
	{
		Null,		//The null address object. Equivalent to CHostAddress()
		Boroadcast,	//The IPv4 broadcast address. Equivalent to CHostAddress("255.255.255.255").
		LocalHost,	//the IPv4 localhost address.Equivalent to CHostAddress("127.0.0.1").
		AnyIPv4 = 6	//The IPv4 any-address. Equivalent to CHostAddress("0.0.0.0")	
	};
public:
	CHostAddress(const string&address);
	CHostAddress(const CHostAddress&address);
	CHostAddress(const sockaddr*sockaddr);
	CHostAddress(cuint32 ipv4addr);
	CHostAddress(CHostAddress::SpecialAddress address);
	CHostAddress();
	~CHostAddress();

	cuint32 toIpv4Address() const;
	string	toString() const;
public:

	bool operator!=(const CHostAddress& other) const;
	bool operator!=(CHostAddress::SpecialAddress other) const;
	bool operator==(const CHostAddress& other) const;
	bool operator==(CHostAddress::SpecialAddress other) const;


private:
	cuint32 address;
	mutable string  addressString;
};
