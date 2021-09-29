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
    int index = 0;
    char buffer[MAX_BUFF_SIZE];
    int msgid = -1;
    int nbytes = -1;

    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);
    if(msgid < 0){
        perror("msgsend msgget fail...");
        exit(1);
    }
    string input_s;

    while(true){
        memset(data.text, 0, MAX_TEXT);
        cin>>input_s;
        data.msg_type = (index++)%4 + 1;
        memcpy(data.text, input_s.c_str(), input_s.length());
        cout<<input_s<<", id : "<<msgid<<endl;
        nbytes = msgsnd(msgid, (void*)&data, MAX_TEXT + 8, 0);
        if (nbytes == -1)
        {
            perror("msgsnd error!!");
            exit(2);
        }
        if(input_s == string("quit")){
            sleep(3);
            break;
        }
        sleep(1);
    }
    return 0;
}