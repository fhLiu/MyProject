#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <errno.h>
#include <sys/msg.h>
#include <string.h>
#include <iostream>
#include <string>

using namespace std;

const unsigned short MAX_TEXT = 512;
const unsigned short MAX_BUFF_SIZE = 1024;

struct msg_st{
    long msg_type;
    char text[MAX_TEXT];
};

int main()
{
    msg_st data;
    int msg_type = 0;
    char buffer[MAX_BUFF_SIZE];
    int msgid = -1;
    int nbytes = -1;

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if(msgid < 0){
        perror("msgrecv msgget fail...");
        exit(1);
    }

    while(true){
        memset(data.text, 0, MAX_TEXT);
        cin>>msg_type;
        cout<<"msg type is : "<<msg_type<<endl;
        nbytes = msgrcv(msgid, (void*)&data, MAX_TEXT+8, msg_type, 0);
        if (nbytes == -1)
        {
            perror("msg recv failed...");
            exit(1);
        }
        cout<<"recv queue recv msg is : "<<data.text<<endl;
        if (strncmp(data.text, "quit", 4) == 0)
        {
            break;
        }
    }

    if(msgctl(msgid, IPC_RMID, 0) == -1)
    {
        perror("rm msgid failed...");
        exit(3);
    }

    return 0;
}