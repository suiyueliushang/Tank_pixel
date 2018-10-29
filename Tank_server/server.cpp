#include"Server.h"


const int magic_num = 114514;
const unsigned int head = 0xECECECEC;



m_server::m_server()
{
	WORD winsock_ver = MAKEWORD(2, 2);
	WSADATA wsa_data;
	WSAStartup(winsock_ver, &wsa_data);
	memset(&server_addr, 0, sizeof(SOCKADDR));
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(tcp_port);
	sock_server = socket(AF_INET, SOCK_STREAM, 0);

	int imode = 1;
	ioctlsocket(sock_server, FIONBIO, (u_long *)&imode);
	int errcode = WSAGetLastError();
	::bind(sock_server, (SOCKADDR *)&server_addr, sizeof(SOCKADDR));
	listen(sock_server, 20);
	join = false;
	thr_acc = new std::thread(&m_server::m_accept, this);
}

m_server::~m_server()
{
	join = true;
	thr_acc->join();
	delete thr_acc;
}

void m_server::m_accept()
{
	SOCKET broadcast;
	broadcast = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);

	SOCKADDR_IN broadcast_addr;
	broadcast_addr.sin_family = AF_INET;
	broadcast_addr.sin_port = htons(udp_port);
	broadcast_addr.sin_addr.s_addr = INADDR_BROADCAST;
	bool bOpt = true;
	setsockopt(broadcast, SOL_SOCKET, SO_BROADCAST, (char*)&bOpt, sizeof(bOpt));
	int imode = 1;
	ioctlsocket(broadcast, FIONBIO, (u_long *)&imode);
	int addlen = sizeof(SOCKADDR);

	int id = 0;
	SOCKET temp_socket;
	SOCKADDR_IN temp_addr;

	char buf[max_buf_size];
	while (!join) {
		if (id < 20)
			sendto(broadcast, (char*)&magic_num, sizeof(int), 0, (sockaddr*)&broadcast_addr, sizeof(sockaddr));
		temp_socket = accept(sock_server, (SOCKADDR *)(&temp_addr), &addlen);

		if (temp_socket != INVALID_SOCKET) {
			while (true) {
				int r_id;
				int c = recv(temp_socket, buf, max_buf_size, 0);
				if (c <= 0) {
					int err = WSAGetLastError();
					if (err == 10057) {
						Sleep(10);
						continue;
					}
					else if (err == 10035) {
						Sleep(10);
						continue;
					}
				}
				memcpy(&r_id, buf, sizeof(int));
				if (r_id < 0) {
					if (id >= 20)break;
					send(temp_socket, (char*)&id, sizeof(int), 0);
					clients[id].status = 1;
					clients[id].sock_server = temp_socket;
					clients[id].addr_clt = temp_addr;
					id++;
				}
				else if (r_id < max_client) {
					send(temp_socket, (char*)&r_id, sizeof(int), 0);
					clients[r_id].status = 1;
					clients[r_id].sock_server = temp_socket;
					clients[r_id].addr_clt = temp_addr;
				}
				break;
			}
		}
		Sleep(10);
	}
	closesocket(broadcast);
}

void m_server::getConnections(int * list)
{
	for (int i = 0; i < max_client; i++)
		list[i] = clients[i].status;
}

void m_server::m_send(int id, int type, const void * start, int len)
{
	if (clients[id].status == 0)return;
	memcpy(clients[id].sendbuf, &head, sizeof(int));
	memcpy(clients[id].sendbuf + sizeof(int), &type, sizeof(int));
	memcpy(clients[id].sendbuf + 2 * sizeof(int), start, len);
	if (send(clients[id].sock_server, clients[id].sendbuf, len + 2 * sizeof(int), 0) == -1)
		clients[id].status = 0;
}

message_info m_server::m_recv(int id)
{
	if (clients[id].status == 0)
		return message_info();
	int retVal = ::recv(clients[id].sock_server, clients[id].recvbuf, max_buf_size, 0);
	if (retVal <= 0)
	{
		if (WSAGetLastError() == 10035)
		{
			clients[id].info.isNew = false;
		}
		else {
			clients[id].info.isNew = false;
			clients[id].status = 0;
		}
	}
	else {
		unsigned int i_head;
		memcpy(&i_head, clients[id].recvbuf, sizeof(int));
		if (i_head != head) {
			clients[id].info.isNew = false;
			return clients[id].info;;
		}
		clients[id].info.isNew = true;
		char * end = strstr(clients[id].recvbuf + 2 * sizeof(int), (const char*)&head);
		if (end != nullptr)
			clients[id].info.size = end - clients[id].recvbuf - 2 * sizeof(int);
		else
			clients[id].info.size = retVal - 2 * sizeof(int);
		memcpy(&clients[id].info.type, clients[id].recvbuf + sizeof(int), sizeof(int));
	}
	return clients[id].info;
}

int m_server::getContent(int id, void * start, int len)
{
	if (clients[id].status == 0)
		return 0;
	if (len <= 0 || len > clients[id].info.size)
		len = clients[id].info.size;
	memcpy(start, clients[id].recvbuf + 2 * sizeof(int), len);
	clients[id].info.isNew = false;
	return len;
}


m_server server;