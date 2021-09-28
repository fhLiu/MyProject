#include "MulThreadProcess.h"
#include <thread>
#include <unistd.h>
#include <mutex>

using namespace std;
const unsigned short MAX_THREAD_NUM = 4;

namespace {
    int total_ticket_num = 20;
}

std::mutex mtx;


void sell_ticket()
{
    for(int i = 0; i < 20; i++)
    {
        mtx.lock();
        if(total_ticket_num > 0){
            sleep(1);
            cout<<"0x"<<std::hex<<std::this_thread::get_id()<<" sell the "<<std::dec<<(20-total_ticket_num + 1)<<"th ticket"<<endl;
            total_ticket_num--;
        }
        mtx.unlock();
    }

    return;
}


int handle_mul_thread()
{
    std::thread th[MAX_THREAD_NUM];
    for(int i = 0; i < MAX_THREAD_NUM; i++)
    {
        th[i] = std::thread(sell_ticket);
    }

    sleep(15);
    for(int i = 0; i < MAX_THREAD_NUM; i++)
    {
        th[i].join();
    }

    return 0;
}