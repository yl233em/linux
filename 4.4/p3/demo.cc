#include<iostream>
#include<vector>
#include<unistd.h>
#include<stdio.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>

typedef void (*head)();
std::vector<head> headlers;

void fun1()
{
	printf("这是一个临时任务1\n");
}
void fun2()
{
	printf("这是一个临时任务2\n");
}

void Load()
{
	headlers.push_back(fun1);
	headlers.push_back(fun2);

}
int main()
{
	pid_t id = fork();
	if(id == 0)
	{
		//子进程
		int cnt = 5;
		while(cnt)
		{
			printf("我是子进程：%d\n",cnt--);
			sleep(1);
		}

	}
	else
	{
		int quit = 0;
		while(!quit)
		{
			int status = 0;
			pid_t ret = waitpid(-1, &status,                    WNOHANG);//非阻塞方式等待
			if(ret >0)
			{
				printf("等待子进程退出成功退出🏇:%d\n",WEXITSTATUS(status));
				quit = 1;
			}
			else if(ret == 0)
			{
				printf("子进程还在运行，父进程做些其他的事情\n");
				if(headlers.empty()) Load();
				for(auto it : headlers)
				{
					it();
				}
			}
			else
			{
				printf("wait失败！\n");
				quit = 1;
			}
			sleep(1);
		}
	}
}
