#define WIN32_LEAN_AND_MEAN//�����������ڵ������������

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
	//--��socket API�����򵥵�TCP�ͻ���
	//1.����һ��socket
	SOCKET _sock=socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock)
	{
		printf("ERROR,�����׽���ʧ��\n");
	}else{
		printf("SUCCESS,�����׽��ֳɹ�\n");
	}
	//2.���ӷ�����connect
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//�������ԣ������ñ���ip
	int ret = connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
	if (SOCKET_ERROR == ret)
	{
		printf("ERROR,���ӷ�����ʧ��\n");
	}
	else {
		printf("SUCCESS,���ӷ������ɹ�\n");
	}

	//3.���ܷ�������Ϣrecv
	char recvBuf[256] = {};
	int nlen = recv(_sock, recvBuf, 256, 0);
	if (nlen > 0)
	{
		printf("�ͻ��˽��յ������ݣ�%s\n", recvBuf);
	}
	//4.�ر��׽���closesocket
	closesocket(_sock);

	//-------------------------
	//���windows socket����
	WSACleanup();//�ر���·����
	getchar();
	return 0;
}