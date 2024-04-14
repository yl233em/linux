#include <iostream>
#include <string>
#include <vector>
#include <functional>
#include <unistd.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <signal.h>
#include <stdlib.h>

using namespace std;

void handler(int sig)
{
    cout << "Handler 捕获了一个信号:" << sig << endl;
    alarm(1);
}



int main()
{
    signal(SIGALRM, handler);

    alarm(1);

    while(1) sleep(1);

    return 0;
}