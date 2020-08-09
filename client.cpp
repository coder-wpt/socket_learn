#define WIN32_LEAN_AND_MEAN//避免引入早期的依赖库的引用

#include <windows.h>
#include <WinSock2.h>
#include <stdio.h>
//1.引入了window头文件之后要调用他的函数需要加入他的静态链接库的文件,不然会报无法解析
//#pragma comment(lib,"ws2_32.lib")
//2.在win下是没有问题，但是在其它系统是不支持的，需要在工程配置属性里，链接器-输入-附加项-加入ws2_32.lib


int main()
{
	//启动windows socket 2.x 环境
	WORD ver = MAKEWORD(2, 2);
	WSADATA dat;
	WSAStartup(ver, &dat);//启动网络环境
	//-------------------------
	//--用socket API建立简单的TCP客户端
	//1.建立一个socket
	SOCKET _sock=socket(AF_INET, SOCK_STREAM, 0);
	if (INVALID_SOCKET == _sock)
	{
		printf("ERROR,建立套接字失败\n");
	}else{
		printf("SUCCESS,建立套接字成功\n");
	}
	//2.链接服务器connect
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;
	_sin.sin_port = htons(4567);
	_sin.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");//本机测试，可以用本机ip
	int ret = connect(_sock, (sockaddr*)&_sin, sizeof(sockaddr_in));
	if (SOCKET_ERROR == ret)
	{
		printf("ERROR,连接服务器失败\n");
	}
	else {
		printf("SUCCESS,连接服务器成功\n");
	}

	//3.接受服务器消息recv
	char recvBuf[256] = {};
	int nlen = recv(_sock, recvBuf, 256, 0);
	if (nlen > 0)
	{
		printf("客户端接收到的数据：%s\n", recvBuf);
	}
	//4.关闭套接字closesocket
	closesocket(_sock);

	//-------------------------
	//清除windows socket环境
	WSACleanup();//关闭网路环境
	getchar();
	return 0;
}