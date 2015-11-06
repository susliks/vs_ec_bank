#include "stdafx.h"
#include "head.h"

ICBCBank::ICBCBank()
{
	int result;
	char * errmsg = NULL;
	char **dbResult; //�� char ** ���ͣ�����*��
	int nRow, nColumn;
	int i, j;
	int index;

	result = sqlite3_open("ICBCData.db", &db);		//TODO:������߼�������
	if (result != SQLITE_CANTOPEN)	//����ʧ�ܣ��򴴽�
	{
		//��ԭ���Ѿ����������ű���򲻻ᴴ����񣬼�����Ӱ����ȷ���У����Բ��ô�����
		string SQLCode = "create table ICBC ";
		SQLCode = SQLCode + "(bank_name varchar(25), card_num varchar(25), password varchar(25), ";
		SQLCode = SQLCode + "client_Id varchar(25), deposit double(20) );";
		result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);	
		

		SQLCode = "create table setting (item varchar(25), num int(25));";
		result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);
		/*if (result != SQLITE_OK)	//������ʧ�� �򱨴�
		{
			cout << "Open database fail: " << sqlite3_errmsg(db);
			//goto QUIT;
		}
		else
		{

		}*/
	}

	cardNumCnt = 0;
	string SQLCode = "insert into setting (item, num) values (\"cardNumCnt\", 0);";
	result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);
	//cout << errmsg;
}

ICBCBank::~ICBCBank()
{
	sqlite3_close(db);
}

bool ICBCBank::addClient(string bankName, string password, string clientId)
{
	int result;
	char * errmsg = NULL;
	string cardNum = int2string(cardNumCnt, 8);


	string SQLCode = "insert into ICBC ";
	SQLCode = SQLCode + "(bank_name, card_num, password, client_Id, deposit)";
	SQLCode = SQLCode + "values(\"" + bankName + "\", \"" + cardNum + "\", \"" + password
		+ "\", \"" + clientId + "\", 0);";

	result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);
	if (result == SQLITE_OK)
	{
		cardNumCnt++;

		char tmp[20];
		string tmp2;
		sprintf(tmp, "%d", cardNumCnt);
		tmp2 = tmp;
		SQLCode = "update setting set num = " + tmp2 + " where item = \"cardNumCnt\"";
		result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);
		//cout << errmsg;

		return true;
	}
	else
	{
		cout << errmsg;
		return false;
	}
	//insert into coffee(id, coffee_name, taste, rank) value("1", "BlueMountain"����well������5��)
}

bool ICBCBank::deleteClient(string cardNum)
{
	int result;
	char * errmsg = NULL;
	
	string SQLCode = "delete from ICBC where card_num = \"" + cardNum + "\";";

	result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);
	if (result == SQLITE_OK)
	{
		return true;
	}
	else
	{
		cout << errmsg;
		return false;
	}
}

void ICBCBank::clientInfoUpdate()
{

}

bool ICBCBank::checkClient()
{
	return true;
}

bool ICBCBank::transaction()
{
	return true;
}
