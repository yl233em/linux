#include <iostream>
#include <signal.h>
#include <unistd.h>
#include <cassert>

static void showPending(sigset_t &pending)
{
    for(int sig = 1; sig <= 31; sig++)
    {
        if(sigismember(&pending, sig))
        {
            std::cout << sig;
        }
        else
        {
            std::cout << ".";
        }
    }
    std::cout << std::endl;
}

static void blocksig(int sig)
{
    sigset_t bset;
    sigemptyset(&bset);
    sigaddset(&bset, sig);
    int n = sigprocmask(SIG_BLOCK, &bset, nullptr);
    assert(n == 0);
    (void)n;
}

int main()
{
    for(int sig = 1; sig <= 31; sig++)
    {
        blocksig(sig);
    }

    sigset_t pending;
    while(true)
    {
        sigpending(&pending);
        showPending(pending);
        sleep(1);
    }

    return 0;
}