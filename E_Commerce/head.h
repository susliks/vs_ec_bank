#include "stdafx.h"
#include "sqlite3.h"
#include "bank.h"
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
	string int2string(int num, int len)	//返回一个长度为len的数字num对应的string
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