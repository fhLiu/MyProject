#include "TcpServer.h"
#include <assert.h>

TcpServerDev::TcpServerDev(string& ip, unsigned short port):server_ip(ip), server_port(port),
								init_fd(-1), conn_fd(-1)
{
	memset(buf, 0, SOCKET_BUFFER_1K);
}

TcpServerDev::~TcpServerDev()
{
	if (init_fd != -1)
	{
		Close(init_fd);
	}
	if (conn_fd != -1)
	{
		Close(conn_fd);
	}
}

int TcpServerDev::Create()
{
	init_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (init_fd <= 0)
	{
		cout<<"create socket failed..."<<endl;
		return -1;
	}
	return 0;
}

int TcpServerDev::Bind()
{
	assert(init_fd > 0);
	sockaddr_in ser_addr;
	bzero(&ser_addr,sizeof(ser_addr));
	ser_addr.sin_family = AF_INET;
	ser_addr.sin_port = htons(server_port);
	ser_addr.sin_addr.s_addr = inet_addr(server_ip.c_str());
	int res = bind(init_fd, (sockaddr *)&ser_addr, sizeof(ser_addr));
	if (res < 0)
	{
		cout<<"bind server ip failed..."<<endl;
		Close(init_fd);
		return -1;
	}
 	return 0;
}

int TcpServerDev::Listen()
{
	assert(init_fd > 0);
	int res = listen(init_fd, MAX_LISTEN_BACK_POOL);
	if (res < 0)
	{
		cerr<<"listen socket failed..."<<endl;
		Close(init_fd);
		return -1;
	}
	return 0;
}

int TcpServerDev::Accept()
{
	assert(init_fd > 0);
	sockaddr_in cli_addr;
	socklen_t len = 0;

	conn_fd = accept(init_fd, (sockaddr*)&cli_addr, &len);
	if (conn_fd <= 0)
	{
		cerr<<"accpet socket failed..."<<endl;
		Close(init_fd);
		return -1;
	}

	cout<<"recv host :"<<inet_ntoa(cli_addr.sin_addr)<<", port : "<<ntohs(((sockaddr_in)cli_addr).sin_port)<<endl;

	return 0;
}

int TcpServerDev::ReadBuf()
{
	int n_bytes = -1;
	n_bytes = read(conn_fd, buf, SOCKET_BUFFER_1K);
	cout<<n_bytes<<endl;
	if(n_bytes < 0)
	{
		cerr<<"server recv msg failed..."<<strerror(errno)<<endl;
	}else if(n_bytes == 0)
	{
		cout<<"client close socket..."<<endl;
	}
	else{
		cout<<"server recv server msg is : "<<string(buf, n_bytes)<<endl;
	}

	return n_bytes;
}

int TcpServerDev::SendBuf()
{
	int n_bytes = -1;
	n_bytes = write(conn_fd, buf, strlen(buf));
	if(n_bytes < 0)
	{
		cerr<<"client send msg failed..."<<strerror(errno)<<endl;
		return -1;
	}
	bzero(buf, SOCKET_BUFFER_1K);
	return 0;
}

int TcpServerDev::Close(int& fd)
{
	close(fd);
	fd = -1;
	return 0;
}

void handle_server_process()
{
	string ip("127.0.0.1");
	TcpServerDev server(ip, server_port);
	server.Create();
	server.Bind();
	server.Listen();
	server.Accept();
	while(true)
	{
		if(server.ReadBuf() <=0)
				break;
		server.SendBuf();
	}
}

#ifdef SIGNAL_RUN

int main(int argc, char* argv[])
{
	handle_server_process();
	return 0;
}

#endif