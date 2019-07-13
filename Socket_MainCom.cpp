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
	hListen = socket(PF_INET, SOCK_STREAM, IPPROTO_TCP);                    //IPV4타입, 연결지향형 소켓, TCP 사용


	SOCKADDR_IN tListenAddr = {};                                           //소켓 구성요소 담을 구조체 생성
	tListenAddr.sin_family = AF_INET;                                       //주소 정보
	tListenAddr.sin_port = htons(PORT);                                     //포트 번호
	tListenAddr.sin_addr.s_addr = htonl(INADDR_ANY);                        //ip주소 설정 - 현재 동작되는 컴퓨터의 ip 주소


	bind(hListen, (SOCKADDR*)& tListenAddr, sizeof(tListenAddr));            //소캣의 주소정보 전달
	listen(hListen, SOMAXCONN);                                              //접속 승인

	SOCKADDR_IN tClntAddr = {};                                              //소켓 정보 담을 구조체 생성
	int iClntSize = sizeof(tClntAddr);                                          
	SOCKET hClient = accept(hListen, (SOCKADDR*)& tClntAddr, &iClntSize);    //접속 요청 수락
	
	socket(hClient);                                                         //채팅 시작
	 
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
		nRcv = recv(hClient, message, sizeof(message) - 1, 0);          //message 받음

		message[nRcv] = '\0';
		a = (message[0] == indi[0]) ? FALSE : TRUE;                    //message가 q인지 판단하기 위함
		if (a == FALSE)
		{
			printf("Close\n");
			break;
		}

		printf("Receive Message : %s", message);
		printf("\nSend Message : ");
		fgets(message, 30, stdin);                                     //message 입력받음
		a = (message[0] == indi[0]) ? FALSE : TRUE;                    //q인지 판단
		if (a == FALSE)
		{
			printf("Close...\n");
			break;
		}

		strLen = strlen(message);
		send(hClient, message, strLen, 0);                            //message 보냄
	}
}