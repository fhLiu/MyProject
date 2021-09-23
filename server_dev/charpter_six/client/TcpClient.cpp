#include "TcpClient.h"
#include <assert.h>


TcpClientDev::TcpClientDev(string& ip, unsigned short port)
			:server_ip(ip), server_port(port), conn_fd(-1)
{
	memset(buf, 0, SOCKET_BUFFER_1K);
}

TcpClientDev::~TcpClientDev()
{

}

int TcpClientDev::Create()
{
	conn_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (conn_fd <= 0)
	{
		cout<<"create socket failed..."<<endl;
		return -1;
	}
	return 0;
}

int TcpClientDev::Connect()
{
	sockaddr_in ser_addr;
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(server_port);
	ser_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());

	int res = connect(conn_fd, (sockaddr*)&ser_addr, sizeof(ser_addr));

	if (res < 0)
	{
		cerr<<"connect setver failed..."<<endl;
		Close(conn_fd);
		return -1;
	}

	cout<<"Connect server "<<server_ip<<" successful.."<<endl;
	return 0;
}

int TcpClientDev::ReadBuf()
{
	int n_bytes = -1;
	n_bytes = read(conn_fd, buf, SOCKET_BUFFER_1K);
	if(n_bytes < 0)
	{
		cerr<<"client recv msg failed..."<<endl;
	}else if(n_bytes == 0)
	{
		cout<<"peer close socket..."<<endl;
	}
	else{
		cout<<"client recv server msg is : "<<string(buf, n_bytes)<<endl;
	}

	return n_bytes;
}

int TcpClientDev::SendBuf()
{
	int n_bytes = -1;
	cin.getline(buf, SOCKET_BUFFER_1K);
	n_bytes = write(conn_fd, buf, strlen(buf));
	if(n_bytes < 0)
	{
		cerr<<"client send msg failed..."<<endl;
		return -1;
	}
	return 0;
}

int TcpClientDev::Close(int& fd)
{
	close(fd);
	fd = -1;
	return 0;
}

void handle_client_process()
{
	string ser_ip("127.0.0.1");
	TcpClientDev client(ser_ip, server_port);
	client.Create();
	client.Connect();
	while(true)
	{
		client.SendBuf();
		if(client.ReadBuf() <= 0)
			break;
	}
}

#ifdef SIGNAL_RUN

int main(int argc, char* argv[])
{
	handle_client_process();
	return 0;
}

#endif