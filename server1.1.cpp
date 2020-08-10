#define WIN32_LEAN_AND_MEAN//避免引入早期的依赖库的引用
#define _WINSOCK_DEPRECATED_NO_WARNINGS//line63 inet_ntoa 错误需要此宏

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
	//--用socket API建立简单的TCP服务器
	
	//1.建立一个socket
	SOCKET _sock=socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);//ip协议、数据类型、传输协议
	
	//2.bind 绑定用于接收客户端连接的网络接口
	sockaddr_in _sin = {};
	_sin.sin_family = AF_INET;//网络ip
	_sin.sin_port = htons(4567);//端口号主机字节序和网络字节序不匹配 host to net unsigned short
	_sin.sin_addr.S_un.S_addr = INADDR_ANY;//本机任意地址  s_un联合体
											//inet_addr("127.0.0.1");//ip本机地址
	if (bind(_sock, (sockaddr*)&_sin, sizeof(_sin)) == SOCKET_ERROR)//判断某个端口是否被绑定
	{
		printf("ERROR，绑定用于接收客户端连接的网络接口\n");
	}
	else
	{
		printf("SUCCESS，绑定端口成功\n");
	}
	
	//3.listen 监听网络端口
	//第二个参数，最大可以等待多少人链接
	if (SOCKET_ERROR == listen(_sock, 5))
	{
		printf("ERROR,监听网络端口失败\n");
	}
	else
	{
		printf("SUCCESS,监听网络端口成功\n");
	}

	//4.accept 等待接收客户端连接
	sockaddr_in clientAddr = {};
	int nAddrLen = sizeof(sockaddr_in);
	SOCKET _cSock = INVALID_SOCKET;
	

	_cSock = accept(_sock, (sockaddr*)&clientAddr, &nAddrLen);
	if (_cSock == INVALID_SOCKET)
	{
		printf("ERROR,接收到无效的客户端SOCKET\n");
	}
	printf("新客户端加入：socket= %d ,ip=%s \n",(int)_cSock , inet_ntoa(clientAddr.sin_addr));

	char _recvBuf[128] = {};
	while (true)//循环重复执行
	{
		//5.接受客户端的请求数据
		int nlen = recv(_cSock, _recvBuf, 128, 0);
		if (nlen <= 0)
		{
			printf("客户端已退出，任务结束\n");
			break;
		}
		printf("收到命令%s!\n", _recvBuf);
		//6.处理请求
		if (0 == strcmp(_recvBuf, "getName"))
		{
			//7.send 向客户端发送一条数据
			char msgBug[] = "xiao ming";
			send(_cSock, msgBug, strlen(msgBug) + 1, 0);
		}
		else if (0 == strcmp(_recvBuf, "getAge"))
		{
			//7.send 向客户端发送一条数据
			char msgBug[] = "age 18";
			send(_cSock, msgBug, strlen(msgBug) + 1, 0);
		}
		else {
			//7.send 向客户端发送一条数据
			char msgBug[] = "what are you seeing？";
			send(_cSock, msgBug, strlen(msgBug) + 1, 0);
		}
	}
	
	//6.关闭套接字closesocket
	closesocket(_sock);
	//-------------------------
	//清除windows socket环境
	WSACleanup();//关闭网路环境

	printf("服务端已退出，任务结束\n");
	getchar();
	return 0;
}
