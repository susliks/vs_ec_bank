#pragma once
#include "head.h"

/*	一个银行抽象为一个大类的原因：
1.从现实出发，各银行提供的业务不同，过程当然也不同，各大银行混为一个大类不合逻辑
2.各大银行均继承自一个大类（”接口“层次），增删银行非常方便，不用改变原有代码	OO原则：对拓展开放，对修改关闭。 封装变化。
3.考虑到各家银行还有无数的分行，所以这么做绝不是一种冗余

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

class ICBCBank : public Bank	//工商银行
{

private:
	sqlite3 * db;
	int cardNumCnt;	//编号计数
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

class ABCBank : public Bank		//农业银行
{

};

class BOCBank : public Bank		//中国银行
{

};

class CCBBank : public Bank		//建设银行
{

}; 
