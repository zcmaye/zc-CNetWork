#ifndef __CGLOBAL_H_
#define __CGLOBAL_H_

using cuint8 = unsigned char;
using cuint16 = unsigned short;
using cuint32 = unsigned int;
using cuint64 = unsigned long long;

#ifdef _DEBUG
#include<stdio.h>
#define print printf
#else
#define print 
#endif


#endif

