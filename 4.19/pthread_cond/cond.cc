#include<iostream>
#include<string>
#include<pthread>
#include<unistd.h>

#define TNUM 4
typedef void (*func_t)(const std::string &name, pthread_mutex_t *pmutx, pthread_cond_t *pcond);





int main()
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    pthread_cond_init(&cond, nullptr);
    pthread_mutex_init(&mutex, nullptr);

    pthread_t tids[TNUM];
    

    return 0;
}