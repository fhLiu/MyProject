#include "MulProcessDeamon.h"
#include <sys/types.h>
#include <unistd.h>
#include <fcntl.h>
#include <sys/wait.h>
#include <string>
#include <iostream>
#include <sys/stat.h>

const unsigned short MAX_FILE = 65535;
using namespace std;

void handle_mul_process_deamon()
{
    pid_t pc;
    int fd, len;
    std::string buf("This is a Dameon\n");
    len = buf.length();
    pc = fork();
    if(pc < 0){
        perror("error fork\n");
        exit(1);
    }else if(pc > 0){
        cout<<"this is a parent process!!"<<endl;
        exit(0);
    }
    setsid();        //second
    chdir("/");     //third
    umask(0);       //forth
    for(int i = 0; i < MAX_FILE; i++)
    {
        close(i);
    } //fiveth
    
    while(true){
        fd = open("/tmp/dameon.log", O_CREAT|O_WRONLY|O_APPEND, 0600);
        if(fd < 0){
            perror("open failed...\n");
            exit(1);
        }
        write(fd, buf.c_str(), len+1);
        close(fd);
        sleep(10);
    }

}