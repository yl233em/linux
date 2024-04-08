#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>

int main()
{
	pid_t pid = fork();

	if(pid > 0)
	{
		sleep(10);
		printf("父进程该结束了\n");
	}
	else if(pid == 0)
	{
		while(1)
		{
			printf("pid = %d, ppid = %d  我一直玩！\n", getpid(), getppid());
			sleep(1);
		}
	}
	else{
		perror("fork");
		exit(1);
	}
	return 0;
}
