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
		case 1:		//�����û�

			break;
		case 2:		//������� ����������� ��� ȡ��

			break;
		case 3:		//�޸��û���Ϣ �������˶��û���Ϣ�Ĳ�ѯ/�˶ԣ� ɾ��/ע���û�

			break;
		
		case 0:		//�˳�
			endFlag = true;
			break;
		}
	}


	return 0;
}

