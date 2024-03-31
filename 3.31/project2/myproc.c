#include<stdio.h>
#include<unistd.h>
#include<sys/types.h>

int main()
{
	printf("I`m parent, pid:%d\n", getpid());
	
	pid_t ret = fork();

	printf("my pid:%d\n",getpid());
	
	sleep(1);
	return 0;
}
