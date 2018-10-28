
#pragma once

#ifndef SERVER_H
#define SERVER_H

#include<Windows.h>
#include<thread>


//#pragma comment(lib,"ws2_32.lib")

const int max_client = 10;
const int max_buf_size = 4096;
const int tcp_port = 11451;
const int udp_port = 14514;

struct message_info {
	int type = 0;
	int size = 0;
	bool isNew = false;
};

struct one_client {
	int status = 0;
	SOCKET sock_server;//一个客户端接口
	SOCKADDR_IN addr_clt;//一个客户端地址

	message_info info;
	char sendbuf[max_buf_size];
	char recvbuf[max_buf_size];
};

class m_server {
public:
	m_server();
	~m_server();

	void m_accept();

	void getConnections(int* list);

	void m_send(int id, int type, const void* start, int len);

	message_info m_recv(int id);

	int getContent(int id, void* start, int len = 0);

	bool broadcasting = true;

private:
	SOCKET sock_server;//客户端接口
	SOCKADDR_IN server_addr;//服务器地址

	bool join;
	std::thread* thr_acc;
	one_client clients[max_client];
};



extern m_server server;

#endif // !SERVER_H