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