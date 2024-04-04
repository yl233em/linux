#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<sys/types.h>
#include<sys/wait.h>
#include<unistd.h>
int code = 0;
int main()
{
	pid_t id = fork();
	if(id < 0)
	{
		perror("fork");
		exit(1);
	}
	else if(id == 0)//子进程
	{
		int cnt = 5;
		while(cnt)
		{
			printf("我是子进程 cnt:%d,pid:%d,ppid:%d\n",cnt,getpid(),getppid());
			cnt--;
		}
		code = 15;
		exit(15);
	}
	else//父进程
	{
		printf("我是父进程,pid:%d,ppid:%d\n",getpid(),getppid());

		int status = 0;
		pid_t ret = waitpid(id,&status,0);
		if(ret > 0)
		{
			printf("等待子进程成功，ret:%d, 子进程收到的信号编号:%d,子进程推出🏇:%d\n",ret, status & 0x7F,(status>>8)&0xFF);
			printf("code:%d\n",code);
		}
	}

	return 0;
}
