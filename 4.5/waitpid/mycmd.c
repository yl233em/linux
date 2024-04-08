#include<stdio.h>
#include<stdlib.h>
#include<string.h>

int main(int argc, char* argv[])
{
	if(argc != 2)
	{
		printf("can not execute!\n");
		exit(1);
	}

	printf("获取环境变量：my_val: %s\n",getenv("my_val"));
	if(strcmp(argv[1], "-a") == 0)
	{
		printf("hello a!\n");
	}
	else if(strcmp(argv[1], "-b") == 0)
	{
		printf("hello b!\n");
	}
	else
	{
		printf("default!\n");
	}
	return 0;
}
