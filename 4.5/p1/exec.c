#include<stdio.h>
#include<stdlib.h>
#include<sys/wait.h>
#include<unistd.h>

#define NUM 16

const char* myfile = "./mycmd";

int main(int argc, char * argv[], char* env[])
{
	char* const _env[NUM] = {(char*)"my_val=134566", NULL};

	pid_t id = fork();

	if(id == 0)//子进程
	{
		printf("子进程开始运行，pid:%d\n", getpid());
		sleep(3);

		execle(myfile,"mycmd", "-a", NULL, _env);
		exit(1);
	}
	else
	{
		printf("父进程开始运行，pid:%d\n", getpid());

		int status = 0;
		pid_t id = waitpid(-1, &status, 0);
		if(id > 0)
		{
			printf("子进程运行完毕。exit code:%d\n",WEXITSTATUS(status));
		}
	}


	return 0;
}
