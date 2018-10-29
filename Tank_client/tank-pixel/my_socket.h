#pragma once

#include<Windows.h>
#include<thread>

const int max_client = 10;
const int max_buf_size = 4096;
const int tcp_port = 11451;
const int udp_port = 14514;

struct message_info {
	int type = 0;
	int size = 0;
	bool isNew = false;
};

class m_client {
public:
	m_client();
	~m_client();

	void m_send(int type, const void* start, int len);

	message_info m_recv();

	//从start位置接受len的消息
	//小于等于0或大于size则默认size
	int getContent(void* start, int len = 0);

	//-1 未检测到服务器
	//0 连接断开，正在重连
	//1 已连接
	int status = -1;

private:

	int id = -1;

	void m_conn();


	SOCKET sock_server;//客户端接口
	SOCKADDR_IN server_addr;//服务器地址

	message_info info;
	char sendbuf[max_buf_size];
	char recvbuf[max_buf_size];

	bool join;
	std::thread* thr_conn;
};

