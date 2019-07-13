#include <stdio.h>
#include <Winsock2.h>
#include <conio.h>
#include <string.h>
#include <stdbool.h>
#pragma comment(lib, "ws2_32")

#define PORT 4578
#define PACKET_SIZE 1024

int socket(SOCKET hClient);


int main() {
	WSADATA wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	SOCKET hListen;
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);                    //IPV4Ÿ��, ���������� ����, TCP ���


	SOCKADDR_IN tListenAddr = {};                                           //���� ������� ���� ����ü ����
	tListenAddr.sin_family = AF_INET;                                       //�ּ� ����
	tListenAddr.sin_port = htons(PORT);                                     //��Ʈ ��ȣ
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);                        //ip�ּ� ���� - ���� ���۵Ǵ� ��ǻ���� ip �ּ�


	bind(hListen, (SOCKADDR*)& tListenAddr, sizeof(tListenAddr));            //��Ĺ�� �ּ����� ����
	listen(hListen, SOMAXCONN);                                              //���� ����

	SOCKADDR_IN tClntAddr = {};                                              //���� ���� ���� ����ü ����
	int iClntSize = sizeof(tClntAddr);                                          
	SOCKET hClient = accept(hListen, (SOCKADDR*)& tClntAddr, &iClntSize);    //���� ��û ����
	
	socket(hClient);                                                         //ä�� ����
	 
	closesocket(hClient);
	closesocket(hListen);
	WSACleanup();
	return 0;
}


int socket(SOCKET hClient) {
	int nRcv, strLen;
	char message[PACKET_SIZE];
	char indi[2] = { 'q' };
	bool a;
	while (1)
	{
		printf("Message Recives .. \n");
		nRcv = recv(hClient, message, sizeof(message) - 1, 0);          //message ����

		message[nRcv] = '\0';
		a = (message[0] == indi[0]) ? FALSE : TRUE;                    //message�� q���� �Ǵ��ϱ� ����
		if (a == FALSE)
		{
			printf("Close\n");
			break;
		}

		printf("Receive Message : %s", message);
		printf("\nSend Message : ");
		fgets(message, 30, stdin);                                     //message �Է¹���
		a = (message[0] == indi[0]) ? FALSE : TRUE;                    //q���� �Ǵ�
		if (a == FALSE)
		{
			printf("Close...\n");
			break;
		}

		strLen = strlen(message);
		send(hClient, message, strLen, 0);                            //message ����
	}
}