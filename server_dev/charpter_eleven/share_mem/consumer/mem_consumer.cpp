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
    shm_stuff->written = 0;
    
    while (true)
    {
        if(shm_stuff->written == 1){
            cout<<"You wrote "<<shm_stuff->text<<endl;
            sleep((rand() % 4));
            shm_stuff->written = 0;
            if (strncmp(shm_stuff->text, "quit", 4) == 0)
            {
                break;
            }
            
        }
    }

    if(shmdt(shared_addr) == -1)
    {
        perror("shmdt error");
        exit(3);
    }

    if (shmctl(shmid, IPC_RMID, 0) == -1)
    {
        perror("shmctl error");
        exit(4);
    }

    return 0;
    
    
}
