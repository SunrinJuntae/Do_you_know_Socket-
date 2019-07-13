#include <stdio.h>
#include <WinSock2.h>
#include <string.h>
#include <stdbool.h>
#pragma comment(lib, "ws2_32")

#define PORT 4578
#define PACKET_SIZE 1024
#define SERVER_IP "192.168.35.99"


void socket(SOCKET hClient);

int main() {
	WSADATA wsaData;                                      
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	
	SOCKET hSocket;
	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);        //IPV4Ÿ��, ���������� ����, TCP ��� 

	SOCKADDR_IN tAddr = {};                                     //����ü ����
	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(PORT);
	tAddr.sin_addr.s_addr = inet_addr(SERVER_IP);               //���� ip�ּ�

	connect(hSocket, (SOCKADDR*)& tAddr, sizeof(tAddr));       //������ ���Ͽ� ����(=bind)

	socket(hSocket);                                           //ä�� ����

	closesocket(hSocket);                                     //���� ����


	WSACleanup();                                              //����
	return 0;
}


void socket(SOCKET hSocket) {                //ä�� �κ�
	int nRcv;
	char message[PACKET_SIZE];
	char indi[2] = { 'q' };                   //q�� ������ ä�� ��
	while (1)
	{
		printf("Message : ");
		fgets(message, 30, stdin);
		BOOL a = (message[0] == indi[0]) ? FALSE : TRUE;       //a �� ä���� ���� ���� �Ǵ�
		printf("%s", message);
		printf("%d", a);
		if (a == FALSE)
		{
			send(hSocket, message, strlen(message), 0);      //q�� ���� server�� ä���� ���� ��
			printf("Close..\n");
			break;
		}
		send(hSocket, message, strlen(message), 0);       //message�� ����
		printf("Message Receives...\n");

		nRcv = recv(hSocket, message, sizeof(message) - 1, 0);        //message�� ����
		 
		message[nRcv] = '\0';                     //�޼��� �ڿ� �ι��� �ٿ���
		a = (message[0] == indi[0]) ? FALSE : TRUE;          //q �Ǵ�
		if (a == FALSE)
		{
			printf("Close Server Connection...\n");
			break;
		}

		printf("Receive Message : %s", message);
	}
}