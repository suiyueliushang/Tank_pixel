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
//	SOCKET sock_clt;//�ͻ��˽ӿ�
//	SOCKADDR_IN addr_clt;//�ͻ��˵�ַ
//	int res_val;
//	int addr_len;//����
//};
//
//class sendData1
//{
//public:
//	int step;//���͵ڼ���������
//	bool start;//�Ƿ�����ʼ��Ϸ
//};
//
//class sendData2
//{
//public:
//	int step;
//	int m_choice;//ѡ���̹��
//	bool is_confume;//�Ƿ���ȷ��
//};
//
//
//
//
//class revData1
//{
//public:
//	int step;//�յڼ��ε���Ϣ
//	int id;//����Ϣ������������
//};
//
//class revData2
//{
//public:
//	int step;
//
//	int id[4];//������ұ��
//	int id_choice[4];//�������ѡ���̹��
//	bool id_confirm[4];//��������Ƿ�ȷ��
//};
//
//#endif