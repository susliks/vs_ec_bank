#pragma once
#include "head.h"

/*	һ�����г���Ϊһ�������ԭ��
1.����ʵ�������������ṩ��ҵ��ͬ�����̵�ȻҲ��ͬ���������л�Ϊһ�����಻���߼�
2.�������о��̳���һ�����ࣨ���ӿڡ���Σ�����ɾ���зǳ����㣬���øı�ԭ�д���	OOԭ�򣺶���չ���ţ����޸Ĺرա� ��װ�仯��
3.���ǵ��������л��������ķ��У�������ô��������һ������

*/
const static double eps = 1e-6;
const static int BUF_LEN = 20;
const int PSW_LEN = 8;	//PASSWORD LENGTH

struct bankClientInfo
{
	string bankName;
	string cardNum;
	string password;
	string clientId;
	double deposit;
};

class Bank
{
private:
	


public:
	virtual bool addClient() = 0;
	virtual bool deleteClient(string cardNum) = 0;
	virtual void clientInfoUpdate() = 0;
	virtual bool checkClient() = 0;
	virtual bool transaction() = 0;
};

class ICBCBank : public Bank	//��������
{

private:
	sqlite3 * db;
	int cardNumCnt;	//��ż���
	void saveCardNumCnt();
	int loadCardNumCnt();
	bool changeDeposit(string cardNum, double amount);
	bool createRecord(string bankName, string password, string clientId);
	bool deleteRecord(string cardNum);
	bool existJudge(string cardNum);
	bool verifyPassword(string cardNum, string password);
	double getDeposit(string cardNum);
	string getPassword(string cardNum);
	string getClientId(string cardNum);
	void setDeposit(string cardNum, double deposit);
	void setPassword(string cardNum, string passward);
	void setClientId(string cardNum, string clientId);
public:
	ICBCBank();
	~ICBCBank();
	bool addClient();
	bool deleteClient(string cardNum);
	void clientInfoUpdate();
	bool checkClient();
	bool transaction();
};

class ABCBank : public Bank		//ũҵ����
{

};

class BOCBank : public Bank		//�й�����
{

};

class CCBBank : public Bank		//��������
{

}; 
