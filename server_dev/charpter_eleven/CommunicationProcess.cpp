#include "CommunicationProcess.h"
#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <wait.h>

using namespace std;

int communication_pipe_process()
{
    int fd[2];
    pid_t pid;
    char buf[256];
    int returned_cnt;
    pipe(fd);

    pid = fork();
    if (pid < 0)
    {
        perror("fork error! \n");
        exit(1);
    }
    else if(pid > 0)
    {
        //parent pid, close write end
        close(fd[1]);
        returned_cnt = read(fd[0], buf, sizeof(buf));
        if(returned_cnt < 0)
        {
            perror("read error...\n");
            exit(1);
        }
        cout<<"read from child pid message is : "<<string(buf, returned_cnt)<<", size is : "<<returned_cnt<<endl;
        waitpid(0, NULL, 0);
        cout<<"parent pid will done!!"<<endl;
        exit(0);
    }
    close(fd[0]);
    string tmp("Hello World!!");
    write(fd[1], tmp.c_str(), tmp.length());

    sleep(3);
    cout<<"child pid will done!!"<<endl;
    return 0;
}

void handle_communication_by_process()
{
    communication_pipe_process();
}