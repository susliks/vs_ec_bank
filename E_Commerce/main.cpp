#include "stdafx.h"
#include "head.h"





int main()
{
	//
	//Tools tools = new Tools;

	//Bank bank1;
	Bank *bank1 = new ICBCBank;
	
	(*bank1).addClient("111", "222", "333");
	//(*bank1).deleteClient("00000001");

	bool endFlag = false;
	while (!endFlag)
	{
		int n;
		cout << "state:";
		cin >> n;
		switch (n)
		{
		case 1:		//增加用户

			break;
		case 2:		//服务界面 包括：查余额 存款 取款

			break;
		case 3:		//修改用户信息 （包含了对用户信息的查询/核对） 删除/注销用户

			break;
		
		case 0:		//退出
			endFlag = true;
			break;
		}
	}


	return 0;
}

