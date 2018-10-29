//#include"client.h"
//#include<iostream>
//#include"winsock2.h"
//using namespace std;
//#pragma comment(lib,"ws2_32.lib")
//
//
//#define MaxSize 500
//#define SER_PORT 8888//端口
//
//
//Client::Client()//构造函数
//{
//	winsock_ver = MAKEWORD(2, 2);//初始化winsock
//	addr_len = sizeof(SOCKADDR_IN);
//	addr_clt.sin_family = AF_INET;
//	addr_clt.sin_port = htons(SER_PORT);
//	addr_clt.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");
//	WSAStartup(winsock_ver, &wsa_data);
//	cout << "WSAStartup successfully..." << endl;
//	//创建socket
//	sock_clt = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
//	//连接服务器
//
//	int imode = 1;
//	ioctlsocket(sock_clt, FIONBIO, (u_long *)&imode);
//
//	connect(sock_clt, (LPSOCKADDR)&addr_clt, addr_len);
//	cout << "Client connect successfully!" << endl;
//}
//
//
//Client::~Client()//析构函数
//{
//	closesocket(sock_clt);
//	WSACleanup();
//	cout << "client close..." << endl;
//}
//
//
//
////void Client::Send()//实现对服务器端进行消息收发
////{
////	while (1)
////	{
////		int retVal;
////		int errcode;
////		retVal = send(sock_clt, (char*)&input, sizeof(input), 0);
////		if (retVal == SOCKET_ERROR)
////		{
////			errcode = WSAGetLastError();
////			if (errcode == WSAEWOULDBLOCK)
////			{
////				Sleep(2000);
////				continue;
////			}
////		}
////	}
////}
//
//void Client::Send()//实现对服务器端进行消息收发
//{
//	int res_val = 0;
//	int errcode;
//	int x = 1;
//	send(sock_clt, (char*)x, sizeof(x),0);
//}
//
//bool Client::Send(int c)
//{
//	send(sock_clt, (char*)c, sizeof(c), 0);
//	return true;
//}
//
//void Client::Send(raw_input &input)
//{
//	send(sock_clt, (char*)&input, 50,0);
//}
//
//int Client::receive()
//{
//	char buff[4];
//	memset(buff, 0, 4);
//	int retVal;
//	int errcode;
//	int s;
//	while (1)
//	{
//		retVal = recv(sock_clt, buff, 4, 0);
//		if (retVal == SOCKET_ERROR)
//		{
//			errcode = WSAGetLastError();
//			if (errcode == WSAEWOULDBLOCK)
//			{
//				continue;
//			}
//		}
//		memcpy(&s, buff, 4);
//		return s;
//	}
//}
//
//bool Client::receive(_dynamicScene &d)
//{
//	char buff[1024];
//	memset(buff, 0, 1024);
//	int retVal;
//	int errcode;
//	retVal = recv(sock_clt, buff, 1024, 0);
//	if (retVal == SOCKET_ERROR)
//		return false;
//	memcpy(&d, buff, 1024);
//	return true;
//}
//
//
//
////void Client::receive()
////{
////	char buffer[1024];
////	memset();
////	recv();
////}
//
//void Client::set_mouse(mouse_msg m)
//{
//	input.m = m;
//	/*memcpy((char *)input.m.msg, (char *)m.msg, sizeof(m.msg));
//	memcpy((char *)input.m.flags, (char *)m.flags, sizeof(m).flags);
//	memcpy((char *)input.m.wheel, (char *)m.wheel, sizeof(m.wheel));
//	memcpy((char *)input.m.x, (char *)m.x, sizeof(m.x));
//	memcpy((char *)input.m.y, (char *)m.y, sizeof(m.y));*/
//}
//
//void Client::set_key(key_msg k)
//{
//	input.k = k;
//	/*memcpy((char *)input.k.key, (char *)k.key, sizeof(k));
//	memcpy((char *)input.k.flags, (char *)k.flags, sizeof(k));
//	memcpy((char *)input.k.msg, (char *)k.msg, sizeof(k));*/
//}
