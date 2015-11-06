#pragma once
#include "head.h"

/*	һ�����г���Ϊһ�������ԭ��
1.����ʵ�������������ṩ��ҵ��ͬ�����̵�ȻҲ��ͬ���������л�Ϊһ�����಻���߼�
2.�������о��̳���һ�����ࣨ���ӿڡ���Σ�����ɾ���зǳ����㣬���øı�ԭ�д���	OOԭ�򣺶���չ���ţ����޸Ĺرա� ��װ�仯��
3.���ǵ��������л��������ķ��У�������ô��������һ������

*/

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
	virtual bool addClient(string bankName, string password, string clientId) = 0;
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

public:
	ICBCBank();
	~ICBCBank();
	bool addClient(string bankName, string password, string clientId);
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
