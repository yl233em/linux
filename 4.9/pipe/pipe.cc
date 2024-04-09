#include<iostream>
#include<string>
#include<cstdio>
#include<cstring>
#include<assert.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/wait.h>

using namespace std;

int main()
{
    int pipefd[2] = {0};
    int n = pipe(pipefd);
  
    assert(n != -1);
    (void)n;//debug

    pid_t id = fork();
    assert(id != -1);

    if(id == 0)//子进程读
    {
        close(pipefd[1]);
        char buff[1024 * 8];

        while(true)
        {
            ssize_t s = read(pipefd[0],buff,sizeof(buff) - 1);
            if(s > 0)//读到了 
            {
                buff[s] = 0;
                cout << "我收到信息了[" << getpid() << "] 来自父进程：" << buff << endl;
            }
            else if(s == 0)//读到文件结尾
            {
                cout << "读完了，我要退出" << endl;
                break;
            }
        }
        exit(0);
    }

    //父进程写
    close(pipefd[0]);
    string message = "我是父进程，给你发消息";
    char send_buff[1024 * 8];
    int count = 0;
    while(true)
    {

        snprintf(send_buff,sizeof(send_buff),"%s[%d] : %d", message.c_str(),getpid(),count++);

        write(pipefd[1],send_buff,strlen(send_buff));
        sleep(1);
        cout << count << endl;

        if(count == 5)
        {
            cout << "我写完了" << endl;
            break;
        }

    }

    close(pipefd[1]);
    pid_t ret = waitpid(id, nullptr, 0);

    return 0;
}