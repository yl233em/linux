#include<stdio.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<stdlib.h>
int main()
{
	printf("当前进程开始代码：\n");
	execl("/usr/bin/ls", "ls", NULL);
	exit(1);
	printf("进程结束代码\n");
	return 0;
}
