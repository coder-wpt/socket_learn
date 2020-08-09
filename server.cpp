#define WIN32_LEAN_AND_MEAN//�����������ڵ������������
#define _WINSOCK_DEPRECATED_NO_WARNINGS//line63 inet_ntoa ������Ҫ�˺�

#include <windows.h>
#include <WinSock2.h>
#include <stdio.h>

//1.������windowͷ�ļ�֮��Ҫ�������ĺ�����Ҫ�������ľ�̬���ӿ���ļ�,��Ȼ�ᱨ�޷�����
//#pragma comment(lib,"ws2_32.lib")
//2.��win����û�����⣬����������ϵͳ�ǲ�֧�ֵģ���Ҫ�ڹ������������������-����-������-����ws2_32.lib


int main()
{
	//����windows socket 2.x ����
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);//�������绷��
	//-------------------------
	//--��socket API�����򵥵�TCP������
	
	//1.����һ��socket
	SOCKET _sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//ipЭ�顢�������͡�����Э��
	
	//2.bind �����ڽ��տͻ������ӵ�����ӿ�
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;//����ip
	_sin.sin_port = htons(4567);//�˿ں������ֽ���������ֽ���ƥ�� host to net unsigned short
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;//���������ַ  s_un������
											//inet_addr("127.0.0.1");//ip������ַ
	if (bind(_sock, (sockaddr*)&_sin, sizeof(_sin)) == SOCKET_ERROR)//�ж�ĳ���˿��Ƿ񱻰�
	{
		printf("ERROR�������ڽ��տͻ������ӵ�����ӿ�\n");
	}
	else
	{
		printf("SUCCESS���󶨶˿ڳɹ�\n");
	}
	
	//3.listen ��������˿�
	//�ڶ��������������Եȴ�����������
	if (SOCKET_ERROR == listen(_sock, 5))
	{
		printf("ERROR,��������˿�ʧ��\n");
	}
	else
	{
		printf("SUCCESS,��������˿ڳɹ�\n");
	}

	//4.accept �ȴ����տͻ�������
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	while (true)//ѭ���ظ�ִ��
	{
		_cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
		if (_cSock == INVALID_SOCKET)
		{
			printf("ERROR,���յ���Ч�Ŀͻ���SOCKET\n");
		}
		printf("�¿ͻ��˼�����ip=%s \n", inet_ntoa(clientAddr.sin_addr));
		//5.send ��ͻ��˷���һ������
		char msgBug[] = "hello,i'm server.";
		send(_cSock, msgBug, strlen(msgBug) + 1, 0);
	}
	
	//6.�ر��׽���closesocket
	closesocket(_sock);
	//-------------------------
	//���windows socket����
	WSACleanup();//�ر���·����
	return 0;
}