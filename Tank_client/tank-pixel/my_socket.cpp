#include "my_socket.h"
#pragma comment(lib,"ws2_32.lib")

const int magic_num = 114514;
const unsigned int head = 0xECECECEC;

m_client::m_client()
{
	WORD winsock_ver = MAKEWORD(2, 2);//³õÊ¼»¯winsock
	WSADATA wsa_data;
	WSAStartup(winsock_ver, &wsa_data);

	join = false;
	thr_conn = new std::thread(&m_client::m_conn, this);
}

m_client::~m_client()
{
	join = true;
	thr_conn->join();
	delete thr_conn;
}

void m_client::m_conn()
{
	SOCKET broadcast;
	sockaddr_in from_addr, recv_addr;
	recv_addr.sin_family = AF_INET;
	recv_addr.sin_addr.s_addr = 0;
	recv_addr.sin_port = htons(udp_port);
	from_addr.sin_family = AF_INET;
	from_addr.sin_addr.s_addr = INADDR_BROADCAST;
	server_addr.sin_family = AF_INET;
	server_addr.sin_port = htons(tcp_port);

	int fromlength = sizeof(SOCKADDR);
	bool optval = true;
	int imode = 1;

	broadcast = socket(AF_INET, SOCK_DGRAM, 0);
	setsockopt(broadcast, SOL_SOCKET, SO_BROADCAST, (char FAR *)&optval, sizeof(optval));
	bind(broadcast, (sockaddr *)&recv_addr, sizeof(sockaddr_in));

	int num = 0;
	while (num != magic_num)
		recvfrom(broadcast, (char*)&num, 4, 0, (struct sockaddr FAR *)&from_addr, (int FAR *)&fromlength);
	closesocket(broadcast);
	status = 0;
	server_addr.sin_addr = from_addr.sin_addr;

	char buf[max_buf_size];
	while (!join) {
		if (status == 1) {
			Sleep(10);
			continue;
		}
		sock_server = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
		ioctlsocket(sock_server, FIONBIO, (u_long *)&imode);
		while (!join) {
			connect(sock_server, (LPSOCKADDR)&server_addr, sizeof(SOCKADDR_IN));
			int c = send(sock_server, (char*)&id, sizeof(int), 0);
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
				else {
					break;
				}
			}
			else {
				while (!join) {
					int c = recv(sock_server, buf, max_buf_size, 0);
					if (c <= 0) {
						if (WSAGetLastError() == 10035) {
							continue;
						}
						else {
							break;
						}
					}
					else {
						memcpy(&id, buf, sizeof(int));
						status = 1;
						break;
					}
				}
			}
			break;
		}
	}

}

void m_client::m_send(int type, const void * start, int len)
{
	if (status <= 0)return;
	memcpy(sendbuf, &head, sizeof(int));
	memcpy(sendbuf + sizeof(int), &type, sizeof(int));
	memcpy(sendbuf + 2 * sizeof(int), start, len);
	if (send(sock_server, sendbuf, len + 2 * sizeof(int), 0) == -1)
		status = 0;
}

message_info m_client::m_recv()
{
	if (status <= 0)return message_info();
	int retVal = ::recv(sock_server, recvbuf, max_buf_size, 0);
	if (retVal <= 0)
	{
		if (WSAGetLastError() == 10035)
		{
			info.isNew = false;
		}
		else {
			info.type = 0;
			info.isNew = false;
			status = 0;
			return info;
		}
	}
	else {
		unsigned int i_head;
		memcpy(&i_head, recvbuf, sizeof(int));
		if (i_head != head)
			return info;
		memcpy(&info.type, recvbuf + sizeof(int), sizeof(int));
		info.isNew = true;
		char * end = strstr(recvbuf + 2 * sizeof(int), (const char*)&head);
		if (end != nullptr)
			info.size = end - recvbuf - 2 * sizeof(int);
		else
			info.size = retVal - 2 * sizeof(int);
	}
	return info;
}

int m_client::getContent(void * start, int len)
{
	if (status <= 0)return 0;
	if (len <= 0 || len > info.size)
		len = info.size;
	memcpy(start, recvbuf + 2 * sizeof(int), len);
	info.isNew = false;
	return len;
}
