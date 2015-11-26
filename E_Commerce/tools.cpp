#include "stdafx.h"
#include "head.h"

string int2string(int num, int len)	//返回一个长度为len的数字num对应的string
{
	num++;
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

string recvMsgAnalyse(char *recvbuf)
{
	int len = strlen(recvbuf);
	string res;

	
	string msg[4];
	int pt = 0;

	for (int i = 0; i < len; i++)	//对输入的字符串进行切分
	{
		if (recvbuf[i] == '\0')
		{
			break;
		}
		if (recvbuf[i] == '\1')
		{
			pt++;
			i++;
			continue;
		}
		msg[pt] = msg[pt] + recvbuf[i];
	}

	Bank *pbank = NULL;
	cout << msg[0].size() << endl;

	//char tmp[] = msg[0].c_str() ;
	if (msg[0] == "ICBC")
	{
		pbank = new ICBCBank;
	}
	//TODO

	if (pbank == NULL)	//银行名字匹配失败
	{
		res = "no such a bank";
		return res;
	}

	//账号验证
	if (pbank->existJudge(msg[1]) == false)	//没有此账号
	{
		res = "no such card number";
		return res;
	}
	if (pbank->verifyPassword(msg[1], msg[2]) == false)//密码错误
	{
		res = "incorrect password";
		return res;
	}
		
	//付款操作
	if (pbank->changeDeposit(msg[1], -atof(msg[3].c_str())) == false)//余额不足
	{
		res = "no enough money";
		return res;
	}

	//若能走到这里，说明付款成功
	res = "YES";
	return res;
}