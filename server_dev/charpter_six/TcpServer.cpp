#include "TcpServer.h"

TcpServerDev::TcpServerDev(string& ip, unsigned short port):server_ip(ip), server_port(port),
								init_fd(-1), conn_fd(-1)
{
	memset(buf, 0, SOCKET_BUFFER_1K);
}

TcpServerDev::~TcpServerDev()
{

}

int TcpServerDev::Create()
{

}

int TcpServerDev::Bind()
{

}

int TcpServerDev::Listen()
{

}

int TcpServerDev::Accept()
{

}

int TcpServerDev::ReadBuf()
{

}

int TcpServerDev::SendBuf()
{
	
}