#include<iostream>
#include<cstdio>
#include<string>
#include<unistd.h>
#include<pthread.h>

using namespace std;

void show(const string& name)
{
    cout << name << ",pid:" << getpid() << " " << "\n" << endl;
}

void *thread_func(void * arg)
{
    const string name = (char *) arg;
    while(true)
    {
        show(name);
        sleep(1);
    }
}
int main()
{
    pthread_t tid[5];
    char name[64];
    for(int i = 0; i < 5; i++)
    {
        snprintf(name, sizeof(name), "%s-%d", "thread", i);
        pthread_create(&tid[i], NULL, thread_func, (void*)name);
        sleep(1);
    }

    while(true)
    {
        cout << "main thread,pid:" << getpid() << endl;
        sleep(3);
    }

}