#include <winsock2.h>
#include <windows.h>
#include <stdio.h>
#include <iostream>
#include <string.h>
#include <fstream>
#include <time.h>
#pragma comment(lib,"ws2_32.lib")
using namespace std;


ifstream cRFile("WEB2PPC.txt"); //ֻ�ɶ�
ofstream cWFile("PPC2WEB.txt"); //ֻ��д




DWORD WINAPI serverRead(LPVOID lpParamter)
{
    SOCKET sClient = *((SOCKET*)lpParamter); //sClient
    whlie(1)
    {
        char revData[255];
        int ret = recv(sClient, revData, 255, 0);
        if(ret>0)
        {
            if(strcmp(revData,"wi")==0){  //infrared  0
                cWFile << "0\n";
            }
            else if(strcmp(revData,"ws")==0){ //smoke  1
                cWFile << "1\n";
            }
        }

        Sleep(500);

    }



    return 0L;

}


int main(int argc, char* argv[])
{
	//��ʼ��WSA
	WORD sockVersion = MAKEWORD(2, 2);
	WSADATA wsaData;
	if (WSAStartup(sockVersion, &wsaData) != 0)
	{
		return 0;
	}

	//�����׽���
	SOCKET slisten = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (slisten == INVALID_SOCKET)
	{
		printf("socket error !");
		return 0;
	}

	//��IP�Ͷ˿�
	struct sockaddr_in sin;
	sin.sin_family = AF_INET;
	sin.sin_port = htons(8888);
	sin.sin_addr.S_un.S_addr = INADDR_ANY;
	if (bind(slisten, (LPSOCKADDR)&sin, sizeof(sin)) == SOCKET_ERROR)
	{
		printf("bind error !");
		return 0;
	}

	//��ʼ����
	if (listen(slisten, 5) == SOCKET_ERROR)
	{
		printf("listen error !");
		return 0;
	}

	//ѭ����������
	SOCKET sClient;
	struct sockaddr_in remoteAddr;
	int nAddrlen = sizeof(remoteAddr);
	//char revData[255];
	printf("�ȴ�����...\n");
	sClient = accept(slisten, (SOCKADDR *)&remoteAddr, &nAddrlen);
    printf("���ܵ�һ�����ӣ�%s \r\n", inet_ntoa(remoteAddr.sin_addr));
    if (sClient == INVALID_SOCKET)
    {
         printf("accept error !");
         return 0;
    }
    HANDLE readThread = CreateThread(NULL,1000,serverRead,(LPVOID*)&sClient,0,NULL);
    CloseHandle(readThread);
    while(1)  //sendServer
    {
         if(){  //�����ļ��޸ĳ���0.2��,����ָ��

            char sendData[255];  //�ļ��е�ָ��

            send(sClient, sendData, strlen(sendData), 0);
         }
         Sleep(1000);
      }
    }
    closesocket(sClient);
	closesocket(slisten);
	WSACleanup();
	return 0;
}


