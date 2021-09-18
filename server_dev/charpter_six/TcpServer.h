#pragma once
#include <iostream>
#include <socket.h>
#include <string>

using namespace std;
const int SOCKET_BUFFER_1K = 1024;
const int SOCKET_BUFFER_2K = 2 * 1024;
const int SOCKET_BUFFER_1M = 1024 * 1024;

struct TcpServerDev
{
	TcpServerDev(string& ip, unsigned short port);
	~TcpServerDev();

	int Create();
	int Bind();
	int Listen();
	int Accept();
	int ReadBuf();
	int SendBuf();

private:
	string server_ip;
	unsigned short server_port;
	int init_fd;
	int conn_fd;
	char buf[SOCKET_BUFFER_1K];
};