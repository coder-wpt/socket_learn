#define WIN32_LEAN_AND_MEAN//�����������ڵ������������

#include <windows.h>
#include <WinSock2.h>

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
	//2.���ӷ�����connect
	//3.���ܷ�������Ϣrecv
	//4.�ر��׽���closesocket
	//--��socket API�����򵥵�TCP������
	//1.����һ��socket
	//2.bind �����ڽ��տͻ������ӵ�����ӿ�
	//3.listen ��������˿�
	//4.accept �ȴ����տͻ�������
	//5.send ��ͻ��˷���һ������
	//6.�ر��׽���closesocket
	//-------------------------
	//���windows socket����
	WSACleanup();//�ر���·����
	return 0;
}