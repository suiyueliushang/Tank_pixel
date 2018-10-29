//#ifndef CLIENT_H
//#define CLIENT_H
//#include"WinSock2.h"
//#include"input.h"
//#include"scene.h"
//#include<graphics.h>
//
//class Client
//{
//public:
//	Client();
//	~Client();
//	void Send();
//	int receive();
//	bool receive(_dynamicScene&);
//	boolend(int);
//	void Send(raw_input&);
//	void set_mouse(mouse_msg);
//	void set_key(key_msg);
//
//
//	WORD winsock_ver;
//	WSADATA wsa_data;
//	SOCKET sock_clt;//客户端接口
//	SOCKADDR_IN addr_clt;//客户端地址
//	int res_val;
//	int addr_len;//长度
//};
//
//class sendData1
//{
//public:
//	int step;//发送第几步的数据
//	bool start;//是否点击开始游戏
//};
//
//class sendData2
//{
//public:
//	int step;
//	int m_choice;//选择的坦克
//	bool is_confume;//是否点击确定
//};
//
//
//
//
//class revData1
//{
//public:
//	int step;//收第几次的消息
//	int id;//该消息传来的玩家序号
//};
//
//class revData2
//{
//public:
//	int step;
//
//	int id[4];//其他玩家编号
//	int id_choice[4];//其他玩家选择的坦克
//	bool id_confirm[4];//其他玩家是否确认
//};
//
//#endif