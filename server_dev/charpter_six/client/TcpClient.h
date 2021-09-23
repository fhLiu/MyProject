#pragma once

#include <iostream>
#include <string>

#include "TcpCommon.h"

using namespace std;


struct TcpClientDev
{
	TcpClientDev(string& ip, unsigned short port);
	~TcpClientDev();

	int Create();
	int Connect();
	int ReadBuf();
	int SendBuf();

private:
	int Close(int& fd);

private:
	string server_ip;
	unsigned short server_port;
	int conn_fd;
	char buf[SOCKET_BUFFER_1K];
};

void handle_client_process();