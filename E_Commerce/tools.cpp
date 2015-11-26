#include "stdafx.h"
#include "head.h"

string int2string(int num, int len)	//����һ������Ϊlen������num��Ӧ��string
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

	for (int i = 0; i < len; i++)	//��������ַ��������з�
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

	if (pbank == NULL)	//��������ƥ��ʧ��
	{
		res = "no such a bank";
		return res;
	}

	//�˺���֤
	if (pbank->existJudge(msg[1]) == false)	//û�д��˺�
	{
		res = "no such card number";
		return res;
	}
	if (pbank->verifyPassword(msg[1], msg[2]) == false)//�������
	{
		res = "incorrect password";
		return res;
	}
		
	//�������
	if (pbank->changeDeposit(msg[1], -atof(msg[3].c_str())) == false)//����
	{
		res = "no enough money";
		return res;
	}

	//�����ߵ����˵������ɹ�
	res = "YES";
	return res;
}