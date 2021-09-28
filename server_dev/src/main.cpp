#include <iostream>
#include "my_math.h"
// #include "TcpServer.h"
// #include "TcpClient.h"
#include "MulThreadProcess.h"
#include "MulProcessDeamon.h"
#include "CommunicationProcess.h"

using namespace std;

int main()
{
	cout<<"hello world!"<<endl;
	handle_math_func();
	// handle_mul_thread();
	// handle_mul_process_deamon();
	handle_communication_by_process();
	return 0;
}