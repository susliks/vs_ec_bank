#include "stdafx.h"
#include "head.h"





int main()
{
	//
	//Tools tools = new Tools;

	//Bank bank1;
	//Bank *bank1 = new ICBCBank;
	
	//(*bank1).addClient();
	//(*bank1).deleteClient("00000001");

	//freopen("in.txt", "r", stdin);

	bool endFlag = false;
	Bank *pBank = NULL;
	while (!endFlag)
	{
		int n;
		cout << "1.add 2.transaction 3.update :";
		cin >> n;
		switch (n)
		{
		case 1:		//增加用户
			pBank = new ICBCBank;
			pBank->addClient();
			delete pBank;
			break;
		case 2:		//服务界面 包括：查余额 存款 取款
			pBank = new ICBCBank;
			pBank->transaction();
			delete pBank;
			break;
		case 3:		//修改用户信息 （包含了对用户信息的查询/核对） 删除/注销用户
			pBank = new ICBCBank;
			pBank->clientInfoUpdate();
			delete pBank;
			break;
		
		case 0:		//退出
			endFlag = true;
			break;
		}
	}


	return 0;
}

