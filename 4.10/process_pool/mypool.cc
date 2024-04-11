#include<iostream>
#include<vector>
#include<unistd.h>
#include<assert.h>
#include<time.h>
#include<sys/wait.h>
#include<sys/types.h>
#include"task.hh"

using namespace std;
#define PROC_NUMS 5

int waittask(int fd, bool &quit)
{
    uint32_t command = 0;
    ssize_t s = read(fd, &command, sizeof(command));
    if(s == 0)
    {
        quit = true;
        return -1;
    }
    assert(s == sizeof(uint32_t));
    return command;
}

void push_task(pid_t who, int fd, uint32_t command)
{
    write(fd, &command, sizeof(command));
    cout << "儿子："<< who << "你去做" << desc[command] << fd << "号文件"<< endl;
}


int main()
{
    load();
    vector<pair<pid_t,int>> pool;
    for(int i = 0; i < PROC_NUMS; ++i)
    {
        int pipefd[2] = {0};
        int n = pipe(pipefd);
        assert(n == 0);
        (void)n;
        pid_t id = fork();
        if(id == 0)//子进程
        {
            close(pipefd[1]);//关闭写文件
            while(true)
            {
                bool quit = false;
                //分配任务，读不到就阻塞等
                int command = waittask(pipefd[0], quit);
                if(quit)
                    break;
                
                if(command >= 0 && command < tasknum())
                {
                    vtask[command]();
                }
                else
                {
                    cout << "无效command:"<< command << endl;
                }
                
            }
            exit(1);

        }

        //父进程
        close(pipefd[0]);//关闭读文件
        pool.push_back(pair<pid_t, int>(id, pipefd[1]));

    }
    //父进程派发任务
    srand(time(nullptr) ^getpid() ^ 10938621);
    while(true)
    {
        //选择任务
        int command = rand() % tasknum();
        //选择进程
        int choice = rand() % pool.size();

        push_task(pool[choice].first, pool[choice].second, command);
        sleep(1);
    }

    for(auto p : pool)//关闭文件
    {
        close(p.second);
    }


    for(auto p: pool)
    {
        waitpid(p.first, nullptr, 0);
    }
    return 0;
}