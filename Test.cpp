#define WIN32_LEAN_AND_MEAN//避免引入早期的依赖库的引用

#include <windows.h>
#include <WinSock2.h>

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
	//2.链接服务器connect
	//3.接受服务器消息recv
	//4.关闭套接字closesocket
	//--用socket API建立简单的TCP服务器
	//1.建立一个socket
	//2.bind 绑定用于接收客户端连接的网络接口
	//3.listen 监听网络端口
	//4.accept 等待接收客户端连接
	//5.send 向客户端发送一条数据
	//6.关闭套接字closesocket
	//-------------------------
	//清除windows socket环境
	WSACleanup();//关闭网路环境
	return 0;
}