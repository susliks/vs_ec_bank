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

		//TODO:һ��ʼ�ٶ��������ݽṹ ȡ������create���
		/*string SQLCode = "create table ICBC ";
		SQLCode = SQLCode + "(bank_name varchar(25), card_num varchar(25), password varchar(25), ";
		SQLCode = SQLCode + "client_Id varchar(25), deposit double(20) );";
		result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);	*/
		

		/*SQLCode = "create table setting (item varchar(25), num int(25));";
		result = sqlite3_exec(db, SQLCode.c_str(), 0, 0, &errmsg);*/
		/*if (result != SQLITE_OK)	//������ʧ�� �򱨴�
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
		//��ѯ�ɹ�
		index = nColumn; //ǰ��˵�� dbResult ǰ���һ���������ֶ����ƣ��� nColumn ������ʼ��������������
		printf("�鵽%d����¼\n", nRow);

		for (i = 0; i < nRow; i++)
		{
			printf("�� %d ����¼\n", i + 1);
			for (j = 0; j < nColumn; j++)
			{
				printf("�ֶ���:%s  > �ֶ�ֵ:%s\n", dbResult[j], dbResult[index]);
				++index; // dbResult ���ֶ�ֵ�������ģ��ӵ�0�������� nColumn - 1���������ֶ����ƣ��ӵ� nColumn ������ʼ�����涼���ֶ�ֵ������һ����ά�ı���ͳ�����б�ʾ������һ����ƽ����ʽ����ʾ
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
	char **dbResult; //�� char ** ���ͣ�����*��
	int nRow, nColumn;

	result = sqlite3_get_table(db, "select * from setting where item = \"cardNumCnt\"", &dbResult, &nRow, &nColumn, &errmsg);
	return atoi(dbResult[3]);	//���ݱ�Ľṹ dbResult[3]���λ�ô�ŵ���cardNumCnt��ֵ
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

bool ICBCBank::deleteClient(string cardNum)	//�����ô�
{
	return true;
}

void ICBCBank::clientInfoUpdate()	//�û���Ϣչʾ �û���Ϣ�޸� �û�ɾ��
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
	if (!verifyPassword(cardNum, inputPassword))	//���������ֱ�ӷ���
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
		if (!verifyPassword(cardNum, inputPassword))	//���������ֱ�ӷ���
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
	if (!verifyPassword(cardNum, inputPassword))	//���������ֱ�ӷ���
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
	if (curDeposit < 0 - eps)	//�����С��0Ԫ
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
	//insert into coffee(id, coffee_name, taste, rank) value("1", "BlueMountain"����well������5��)
}

bool ICBCBank::deleteRecord(string cardNum)
{
	int result;
	char * errmsg = NULL;
	char **dbResult; //�� char ** ���ͣ�����*��
	int nRow, nColumn;


	//����˴�Ҫɾ��������Ŀ��nRow��Ϊ����������Ŀ��Ŀ����Ҫɾ������Ŀ��Ŀ
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
	char **dbResult; //�� char ** ���ͣ�����*��
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
	char **dbResult; //�� char ** ���ͣ�����*��
	int nRow, nColumn;

	string SQLCode = "select * from ICBC where card_num = \"" + cardNum + "\";";
	result = sqlite3_get_table(db, SQLCode.c_str(), &dbResult, &nRow, &nColumn, &errmsg);

	return atof(dbResult[9]);	//���ݱ�Ľṹ dbResult[9]���λ�ô�ŵ���deposit��ֵ
}

string ICBCBank::getPassword(string cardNum)	//�ٶ�����һ�������ظ������ѯ��¼ֻ������һ��
{
	int result;
	char * errmsg = NULL;
	char **dbResult; //�� char ** ���ͣ�����*��
	int nRow, nColumn;

	string SQLCode = "select * from ICBC where card_num = \"" + cardNum + "\";";
	result = sqlite3_get_table(db, SQLCode.c_str(), &dbResult, &nRow, &nColumn, &errmsg);
	//cout << endl << errmsg << endl;
	//cout << nRow;
	string tmp = dbResult[7];
	return tmp;	//���ݱ�Ľṹ dbResult[7]���λ�ô�ŵ���password��ֵ
}

string ICBCBank::getClientId(string cardNum)
{
	int result;
	char * errmsg = NULL;
	char **dbResult; //�� char ** ���ͣ�����*��
	int nRow, nColumn;

	string SQLCode = "select * from ICBC where card_num = \"" + cardNum + "\";";
	result = sqlite3_get_table(db, SQLCode.c_str(), &dbResult, &nRow, &nColumn, &errmsg);

	return dbResult[8];	//���ݱ�Ľṹ dbResult[8]���λ�ô�ŵ���clientId��ֵ
}

void ICBCBank::setDeposit(string cardNum, double deposit)
{
	char tmp[20];
	string tmp2;
	sprintf(tmp, "%f", deposit);	//TODO��δ֪�ɲ����е�д��
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

			//�Խ��ܵ�����Ϣ���з��� ��������Ӧ�����Ľ��
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