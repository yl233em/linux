#include<iostream>
#include<thread>
#include<cerrno>
#include<cstring>
#include<unistd.h>
#include<pthread.h>
#include<cstdio>

using namespace std;

int tickets = 10000;

void *gettickets(void *arg)
{
    while(true)
    {
        if(tickets > 0)
        {
            usleep(1000);
            printf("thread:%s,p:%lu  tick:%d\n",(char*)arg,pthread_self(), tickets);
            tickets--;
        }   
        else
        {
            break;
        }
    }
    return nullptr;

}

int main()
{
    pthread_t t1, t2, t3;

    pthread_create(&t1, nullptr, gettickets, (void*)"thread 1");
    pthread_create(&t2, nullptr, gettickets, (void*)"thread 2");
    pthread_create(&t3, nullptr, gettickets, (void*)"thread 3");

    pthread_join(t1, nullptr);
    pthread_join(t2, nullptr);
    pthread_join(t3, nullptr);



}