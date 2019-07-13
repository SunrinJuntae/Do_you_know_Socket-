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
	hSocket = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);        //IPV4타입, 연결지향형 소켓, TCP 사용 

	SOCKADDR_IN tAddr = {};                                     //구조체 생성
	tAddr.sin_family = AF_INET;
	tAddr.sin_port = htons(PORT);
	tAddr.sin_addr.s_addr = inet_addr(SERVER_IP);               //서버 ip주소

	connect(hSocket, (SOCKADDR*)& tAddr, sizeof(tAddr));       //지정된 소켓에 연결(=bind)

	socket(hSocket);                                           //채팅 시작

	closesocket(hSocket);                                     //소켓 닫음


	WSACleanup();                                              //정리
	return 0;
}


void socket(SOCKET hSocket) {                //채팅 부분
	int nRcv;
	char message[PACKET_SIZE];
	char indi[2] = { 'q' };                   //q를 누르면 채팅 끔
	while (1)
	{
		printf("Message : ");
		fgets(message, 30, stdin);
		BOOL a = (message[0] == indi[0]) ? FALSE : TRUE;       //a 로 채팅을 끌지 말지 판단
		printf("%s", message);
		printf("%d", a);
		if (a == FALSE)
		{
			send(hSocket, message, strlen(message), 0);      //q를 보내 server도 채팅을 끄게 함
			printf("Close..\n");
			break;
		}
		send(hSocket, message, strlen(message), 0);       //message를 보냄
		printf("Message Receives...\n");

		nRcv = recv(hSocket, message, sizeof(message) - 1, 0);        //message를 받음
		 
		message[nRcv] = '\0';                     //메세지 뒤에 널문자 붙여줌
		a = (message[0] == indi[0]) ? FALSE : TRUE;          //q 판단
		if (a == FALSE)
		{
			printf("Close Server Connection...\n");
			break;
		}

		printf("Receive Message : %s", message);
	}
}