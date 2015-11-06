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


	return 0;
}

