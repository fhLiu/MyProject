#pragma once
#include <iostream>
#include <string>

#include "TcpCommon.h"

using namespace std;


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
	int Close(int& fd);

private:
	string server_ip;
	unsigned short server_port;
	int init_fd;
	int conn_fd;
	char buf[SOCKET_BUFFER_1K];
};