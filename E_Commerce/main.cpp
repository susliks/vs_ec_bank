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
		case 1:		//�����û�
			pBank = new ICBCBank;
			pBank->addClient();
			delete pBank;
			break;
		case 2:		//������� ����������� ��� ȡ��
			pBank = new ICBCBank;
			pBank->transaction();
			delete pBank;
			break;
		case 3:		//�޸��û���Ϣ �������˶��û���Ϣ�Ĳ�ѯ/�˶ԣ� ɾ��/ע���û�
			pBank = new ICBCBank;
			pBank->clientInfoUpdate();
			delete pBank;
			break;
		
		case 0:		//�˳�
			endFlag = true;
			break;
		}
	}


	return 0;
}

