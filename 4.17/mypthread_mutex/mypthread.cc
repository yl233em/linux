#include<iostream>
#include<thread>
#include<cerrno>
#include<cstring>
#include<unistd.h>
#include<pthread.h>
#include<cstdio>

#define NUM 4
using namespace std;

class thread_data
{
public:
    thread_data(const string& data, pthread_mutex_t *pm)
    :tname(data)
    ,mutex(pm)
    {}
public:
    string tname;
    pthread_mutex_t *mutex;
};


int tickets = 10000;
//全局的互斥锁
//pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
void *gettickets(void *arg)
{
    thread_data *td = (thread_data*)arg;
    while(true)
    {
        pthread_mutex_lock(td->mutex);
        if(tickets > 0)
        {
            usleep(1000);
            tickets--;
            pthread_mutex_unlock(td->mutex);
            printf("thread:%s,  tick:%d\n",td->tname.c_str(), tickets);
        }   
        else
        {
            pthread_mutex_unlock(td->mutex);
            break;
        }
    }
    return nullptr;

}

int main()
{
    //线程ID(本质是共享区地址)
    pthread_t t[NUM];
    //在主线程设置一个互斥锁
    pthread_mutex_t mutex;
    pthread_mutex_init(&mutex, NULL);
    for(int i = 0; i < NUM; i++)
    {
        string name = "thread";
        name += to_string(i);
        thread_data *data = new thread_data(name, &mutex);
        pthread_create(t+i, nullptr, gettickets, (void*)data);
    }
    
    
    //等待线程结束
    for(int i = 0 ; i < NUM; ++i)
    {
        pthread_join(t[i], nullptr);
    }
    pthread_mutex_destroy(&mutex);


}