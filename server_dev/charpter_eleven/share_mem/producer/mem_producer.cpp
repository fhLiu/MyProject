#include "../mem_common.h"
#include <unistd.h>
#include <stdlib.h>
#include <iostream>
#include <string.h>
#include <sys/types.h>
#include <sys/shm.h>
#include <errno.h>

using namespace std;

int main()
{
    int shmid;
    srand((unsigned int)getpid());
    shmid = shmget((key_t)shm_key_s, sizeof(SharedUseSt), 0666| IPC_CREAT);
    if (shmid == -1)
    {
        perror("shmget error.");
        exit(1);
    }

    void* shared_addr = nullptr;
    shared_addr = shmat(shmid, nullptr, 0);
    if(shared_addr == (void*)-1){
        perror("shmar error.");
        exit(2);
    }
    cout<<"Memory atatched at :0x"<<std::hex<<shared_addr<<std::dec<<endl;
    SharedUseSt *shm_stuff;
    shm_stuff = (SharedUseSt*)shared_addr;
    string input_s;
    char buff[512];
    while (true)
    {
        if (shm_stuff->written == 1)
        {
            sleep(1);
            cout<<"waiting for client..."<<endl;
        }

        cout<<"enter sonme text:";
        cin>>input_s;
        memcpy(shm_stuff->text, input_s.c_str(), input_s.length());
        shm_stuff->written = 1;
        
        if(strncmp(shm_stuff->text, "quit", 4) == 0)
        {
            sleep(1);
            break;
        }
    }

    if (shmdt(shared_addr) == -1)
    {
        perror("shmdt error");
        exit(2);
    }
    
    return 0;
}