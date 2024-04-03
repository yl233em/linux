#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	pid_t pid = fork();
	if(pid > 0)//父进程
	{
		while(1)
		{
			printf("好玩！\n");
			sleep(1);
		}

	}
	else
	{
		if(pid == 0)
		{
			sleep(10);
			printf("我死了！\n");}
		else
		{
			perror("fork");
			exit(1);
		}
	}

	

	return 0;
}
