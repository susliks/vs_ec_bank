//#pragma once
#include "stdafx.h"
#include "sqlite3.h"
#include "bank.h"
#include "bankIO.h"
#include <iostream>
#include <cstring>
#include <cstdlib>
#include <cstdio>

using namespace std;



/*
class Tools
{
private:
	int a;
public:
	string int2string(int num, int len)	//����һ������Ϊlen������num��Ӧ��string
	{
		char tmpCh[25];
		sprintf(tmpCh, "%d", num);
		string tmpString = tmpCh;
		int deltaLen = len - tmpString.length();
		for (int i = 0; i < deltaLen; i++)
		{
			tmpString = "0" + tmpString;
		}
		return tmpString;
	}
};*/

class Bank;
class ICBCBank;
string int2string(int num, int len);
string recvMsgAnalyse(char *recvbuf);
bool bank_connect();
bool connection();

#undef UNICODE

#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")
// #pragma comment (lib, "Mswsock.lib")

#define DEFAULT_BUFLEN 512
#define DEFAULT_PORT "27015"