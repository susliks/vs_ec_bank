#include "stdafx.h"
#include "head.h"

ICBCBank::ICBCBank()
{
	int result;
	char * errmsg = NULL;
	char **dbResult; //是 char ** 类型，两个*号
	int nRow, nColumn;
	int i, j;
	int index;

	result = sqlite3_open("ICBCData.db", &db);		//TODO:这里的逻辑有问题
	if (result != SQLITE_CANTOPEN)	//若打开失败，则创建
	{
		//若原来已经存在有这张表格，则不会创建表格，即不会影响正确运行，所以不用错误检测

		//TODO:一开始假定已有数据结构 取消所有create语句
		/*string SQLCode = "create table ICBC ";
		SQLCode = SQLCode + "(bank_name varchar(25), card_num varchar(25), password varchar(25), ";
		SQLCode = SQLCode + "client_Id varchar(25), deposit double(20) );";
		result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);	*/
		

		/*SQLCode = "create table setting (item varchar(25), num int(25));";
		result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);*/
		/*if (result != SQLITE_OK)	//若创建失败 则报错
		{
			cout << "Open database fail: " << sqlite3_errmsg(db);
			//goto QUIT;
		}
		else
		{

		}*/
	}

	//result = sqlite3_get_table(db, "select * from setting where item = \"cardNumCnt\"", &dbResult, &nRow, &nColumn, &errmsg);
	/*if (SQLITE_OK == result)
	{
		//查询成功
		index = nColumn; //前面说过 dbResult 前面第一行数据是字段名称，从 nColumn 索引开始才是真正的数据
		printf("查到%d条记录\n", nRow);

		for (i = 0; i < nRow; i++)
		{
			printf("第 %d 条记录\n", i + 1);
			for (j = 0; j < nColumn; j++)
			{
				printf("字段名:%s  > 字段值:%s\n", dbResult[j], dbResult[index]);
				++index; // dbResult 的字段值是连续的，从第0索引到第 nColumn - 1索引都是字段名称，从第 nColumn 索引开始，后面都是字段值，它把一个二维的表（传统的行列表示法）用一个扁平的形式来表示
			}
			printf("------ - \n");
		}
	}*/

	
	cardNumCnt = this->loadCardNumCnt();
	/*string SQLCode = "insert into setting (item, num) values (\"cardNumCnt\", 0);";
	result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);*/
	//cout << errmsg;
}

ICBCBank::~ICBCBank()
{
	sqlite3_close(db);
}

void ICBCBank::saveCardNumCnt()
{
	char tmp[20];
	string tmp2;
	sprintf(tmp, "%d", cardNumCnt);
	tmp2 = tmp;

	int result;
	char * errmsg = NULL;

	string SQLCode = "update setting set num = " + tmp2 + " where item = \"cardNumCnt\"";
	result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);
}

int ICBCBank::loadCardNumCnt()
{
	int result;
	char * errmsg = NULL;
	char **dbResult; //是 char ** 类型，两个*号
	int nRow, nColumn;

	result = sqlite3_get_table(db, "select * from setting where item = \"cardNumCnt\"", &dbResult, &nRow, &nColumn, &errmsg);
	return atoi(dbResult[3]);	//根据表的结构 dbResult[3]这个位置存放的是cardNumCnt的值
}

bool ICBCBank::addClient()
{
	char tmpBuf[BUF_LEN];
	cout << "password:";
	cin >> tmpBuf;
	string password = tmpBuf;
	cout << "clientId:";
	cin >> tmpBuf;
	string clientId = tmpBuf;

	createRecord("ICBC", password, clientId);

	string cardNum = int2string(this->cardNumCnt, PSW_LEN);
	cout << "your cardNum:" << cardNum.c_str() << endl;

	return true;
}

bool ICBCBank::deleteClient(string cardNum)	//暂无用处
{
	return true;
}

void ICBCBank::clientInfoUpdate()	//用户信息展示 用户信息修改 用户删除
{
	char tmpBuf[BUF_LEN];
	cout << "cardNum:";
	string cardNum;
	cin >> tmpBuf;
	cardNum = tmpBuf;

	cout << "password:";
	string inputPassword;
	cin >> tmpBuf;
	inputPassword = tmpBuf;
	if (!verifyPassword(cardNum, inputPassword))	//若密码错误，直接返回
	{
		return;
	}

	double deposit = this->getDeposit(cardNum);
	string clientId = this->getClientId(cardNum);

	cout << "1.nothing 2.change password 3.change clientId 4.delete clientId:";
	int n;
	cin >> n;
	if (n == 2)
	{
		char tmpBuf[BUF_LEN];
		string newPassword;
		cin >> tmpBuf;
		newPassword = tmpBuf;
		this->setPassword(cardNum, newPassword);
	}
	else if (n == 3)
	{
		char tmpBuf[BUF_LEN];
		string newClientId;
		cin >> tmpBuf;
		newClientId = tmpBuf;
		this->setPassword(cardNum, newClientId);
	}
	else if (n == 4)
	{
		char tmpBuf[BUF_LEN];
		cout << "password:";
		string inputPassword;
		cin >> tmpBuf;
		inputPassword = tmpBuf;
		if (!verifyPassword(cardNum, inputPassword))	//若密码错误，直接返回
		{
			return;
		}
		this->deleteRecord(cardNum);
	}

}

bool ICBCBank::checkClient()
{
	return true;
}

bool ICBCBank::transaction()
{
	char tmpBuf[BUF_LEN];
	cout << "cardNum:";
	string cardNum;
	cin >> tmpBuf;
	cardNum = tmpBuf;

	cout << "password:";
	string inputPassword;
	cin >> tmpBuf;
	inputPassword = tmpBuf;
	if (!verifyPassword(cardNum, inputPassword))	//若密码错误，直接返回
	{
		return false;
	}

	cout << "1.check money 2.save 3.take 4.nothing : ";
	int n;
	cin >> n;

	if (n == 1)
	{
		double deposit = this->getDeposit(cardNum);
		cout << "deposit:" << deposit << endl;
	}
	else if (n == 2)
	{
		double amount;
		cin >> amount;
		this->changeDeposit(cardNum, amount);
	}
	else if (n == 3)
	{
		double amount;
		cin >> amount;
		this->changeDeposit(cardNum, -amount);
	}

	return true;
}

bool ICBCBank::changeDeposit(string cardNum, double amount)
{
	double preDeposit = this->getDeposit(cardNum);
	double curDeposit = preDeposit + amount;
	if (curDeposit < 0 - eps)	//若存款小于0元
		return false;
	else
	{
		this->setDeposit(cardNum, curDeposit);
		return true;
	}
}
bool ICBCBank::createRecord(string bankName, string password, string clientId)
{
	string cardNum = int2string(cardNumCnt, PSW_LEN);
	int result;
	char * errmsg = NULL;

	string SQLCode = "insert into ICBC ";
	SQLCode = SQLCode + "(bank_name, card_num, password, client_Id, deposit)";
	SQLCode = SQLCode + "values(\"" + bankName + "\", \"" + cardNum + "\", \"" + password
		+ "\", \"" + clientId + "\", 0);";

	result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);
	if (result == SQLITE_OK)
	{
		cardNumCnt++;
		this->saveCardNumCnt();

		//cout << errmsg;

		return true;
	}
	else
	{
		cout << errmsg;
		return false;
	}
	//insert into coffee(id, coffee_name, taste, rank) value("1", "BlueMountain"，“well”，“5”)
}

bool ICBCBank::deleteRecord(string cardNum)
{
	int result;
	char * errmsg = NULL;
	char **dbResult; //是 char ** 类型，两个*号
	int nRow, nColumn;


	//计算此次要删掉多少条目，nRow即为检索到的条目数目，即要删除的条目数目
	result = sqlite3_get_table(db, "select * from setting where item = \"cardNumCnt\"", &dbResult, &nRow, &nColumn, &errmsg);

	string SQLCode = "delete from ICBC where card_num = \"" + cardNum + "\";";
	result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);

	if (result == SQLITE_OK)
	{
		cardNumCnt = cardNumCnt - nRow;
		this->saveCardNumCnt();

		return true;
	}
	else
	{
		cout << errmsg;
		return false;
	}
}

bool ICBCBank::existJudge(string cardNum)
{
	int result;
	char * errmsg = NULL;
	char **dbResult; //是 char ** 类型，两个*号
	int nRow, nColumn;

	string SQLCode = "select * from ICBC where card_num = \"" + cardNum + "\";";
	result = sqlite3_get_table(db, SQLCode.c_str(), &dbResult, &nRow, &nColumn, &errmsg);

	if (nRow > 0)
		return true;
	else
		return false;
}

bool ICBCBank::verifyPassword(string cardNum, string inputPassword)
{
	string password = this->getPassword(cardNum);

	if (password == inputPassword)
		return true;
	else
		return false;
}

double ICBCBank::getDeposit(string cardNum)
{
	int result;
	char * errmsg = NULL;
	char **dbResult; //是 char ** 类型，两个*号
	int nRow, nColumn;

	string SQLCode = "select * from ICBC where card_num = \"" + cardNum + "\";";
	result = sqlite3_get_table(db, SQLCode.c_str(), &dbResult, &nRow, &nColumn, &errmsg);

	return atof(dbResult[9]);	//根据表的结构 dbResult[9]这个位置存放的是deposit的值
}

string ICBCBank::getPassword(string cardNum)	//假定卡号一定不会重复，则查询记录只可能有一条
{
	int result;
	char * errmsg = NULL;
	char **dbResult; //是 char ** 类型，两个*号
	int nRow, nColumn;

	string SQLCode = "select * from ICBC where card_num = \"" + cardNum + "\";";
	result = sqlite3_get_table(db, SQLCode.c_str(), &dbResult, &nRow, &nColumn, &errmsg);
	//cout << endl << errmsg << endl;
	//cout << nRow;
	string tmp = dbResult[7];
	return tmp;	//根据表的结构 dbResult[7]这个位置存放的是password的值
}

string ICBCBank::getClientId(string cardNum)
{
	int result;
	char * errmsg = NULL;
	char **dbResult; //是 char ** 类型，两个*号
	int nRow, nColumn;

	string SQLCode = "select * from ICBC where card_num = \"" + cardNum + "\";";
	result = sqlite3_get_table(db, SQLCode.c_str(), &dbResult, &nRow, &nColumn, &errmsg);

	return dbResult[8];	//根据表的结构 dbResult[8]这个位置存放的是clientId的值
}

void ICBCBank::setDeposit(string cardNum, double deposit)
{
	char tmp[20];
	string tmp2;
	sprintf(tmp, "%f", deposit);	//TODO：未知可不可行的写法
	tmp2 = tmp;

	int result;
	char * errmsg = NULL;

	string SQLCode = "update ICBC set deposit = " + tmp2 + " where card_num = \"" + cardNum + "\"";
	result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);
}


void ICBCBank::setPassword(string cardNum, string password)
{
	int result;
	char * errmsg = NULL;

	string SQLCode = "update ICBC set password = " + password + " where card_num = \"" + cardNum + "\"";
	result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);
}

void ICBCBank::setClientId(string cardNum, string clientId)
{
	int result;
	char * errmsg = NULL;

	string SQLCode = "update ICBC set clientId = " + clientId + " where card_num = \"" + cardNum + "\"";
	result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);
}

bool bank_connect()
{
	WSADATA wsaData;
	int iResult;

	SOCKET ListenSocket = INVALID_SOCKET;
	SOCKET ClientSocket = INVALID_SOCKET;

	struct addrinfo *result = NULL;
	struct addrinfo hints;

	int iSendResult;
	char recvbuf[DEFAULT_BUFLEN];
	int recvbuflen = DEFAULT_BUFLEN;

	// Initialize Winsock
	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
		return 1;
	}

	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_INET;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;
	hints.ai_flags = AI_PASSIVE;

	// Resolve the server address and port
	iResult = getaddrinfo(NULL, DEFAULT_PORT, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
		return 1;
	}

	// Create a SOCKET for connecting to server
	ListenSocket = socket(result->ai_family, result->ai_socktype, result->ai_protocol);
	if (ListenSocket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		freeaddrinfo(result);
		WSACleanup();
		return 1;
	}

	// Setup the TCP listening socket
	iResult = bind(ListenSocket, result->ai_addr, (int)result->ai_addrlen);
	if (iResult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		freeaddrinfo(result);
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	freeaddrinfo(result);

	iResult = listen(ListenSocket, SOMAXCONN);
	if (iResult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// Accept a client socket
	ClientSocket = accept(ListenSocket, NULL, NULL);
	if (ClientSocket == INVALID_SOCKET) {
		printf("accept failed with error: %d\n", WSAGetLastError());
		closesocket(ListenSocket);
		WSACleanup();
		return 1;
	}

	// No longer need server socket
	closesocket(ListenSocket);

	string sendMsg = "YES!";

	// Receive until the peer shuts down the connection
	do {

		iResult = recv(ClientSocket, recvbuf, recvbuflen, 0);

		recvbuf[iResult] = '\0';
		cout << recvbuf << endl;
		if (iResult > 0) {

			//对接受到的信息进行分析 并返回相应操作的结果
			sendMsg = recvMsgAnalyse(recvbuf);
			printf("Bytes received: %d\n", iResult);

			// Echo the buffer back to the sender
			iSendResult = send(ClientSocket, sendMsg.c_str(), sendMsg.length(), 0);
			if (iSendResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ClientSocket);
				WSACleanup();
				return 1;
			}
			printf("Bytes sent: %d\n", iSendResult);
		}
		else if (iResult == 0)
			printf("Connection closing...\n");
		else {
			printf("recv failed with error: %d\n", WSAGetLastError());
			closesocket(ClientSocket);
			WSACleanup();
			return 1;
		}

	} while (iResult > 0);

	// shutdown the connection since we're done
	iResult = shutdown(ClientSocket, SD_SEND);
	if (iResult == SOCKET_ERROR) {
		printf("shutdown failed with error: %d\n", WSAGetLastError());
		closesocket(ClientSocket);
		WSACleanup();
		return 1;
	}

	// cleanup
	closesocket(ClientSocket);
	WSACleanup();

	return 0;
}