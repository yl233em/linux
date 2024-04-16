#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <cassert>

using namespace std;

void showpending(sigset_t *pending)
{
    for(int sig = 1; sig <= 31; sig++)
    {
        if(sigismember(pending, sig)) cout << "1";
        else cout << "0";
    }
    cout << endl;
}


void handler(int signum)
{
    cout << "获取了一个信号： " << signum << endl;

    sigset_t pending;
    int c = 20;
    while(c--)
    {
        sigpending(&pending);
        showpending(&pending);
        sleep(1);
    }

}

int main()
{

    signal(2,SIG_IGN);
    cout << "pid = " << getpid() << endl;
    struct sigaction action,oaction;
    action.sa_flags = 0;
    sigemptyset(&action.sa_mask);
    action.sa_handler = handler;

    sigaddset(&action.sa_mask, 3);
    sigaddset(&action.sa_mask, 4);
    sigaddset(&action.sa_mask, 5);
    sigaddset(&action.sa_mask, 6);
    sigaddset(&action.sa_mask, 7);

    sigaction(2, &action, &oaction);

    cout << "默认 action" << (int)(oaction.sa_handler) << endl;

    while(true)sleep(1);
    return 0;
}