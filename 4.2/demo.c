#include<stdio.h>
#include<unistd.h>
#include<stdlib.h>
int uninit;
int inita = 100;
int main(int argc, char* argv[], char* env[])
{
	char* ret = (char*)malloc(10);
	char* ret1 = (char*)malloc(10);
	char* ret2 = (char*)malloc(10);
	char* ret3 = (char*)malloc(10);
	printf("uninit:%p\n",&uninit);
	printf("inita:%p\n",&inita);
	printf("heap:%p\n",ret);
	printf("heap:%p\n",ret1);
	printf("heap:%p\n",ret2);
	printf("heap:%p\n",ret3);
	printf("stack:%p\n",&ret);
	printf("stack:%p\n",&ret1);
	printf("stack:%p\n",&ret2);
	printf("stack:%p\n",&ret3);
	for(int i = 0; i < argc; ++i)
	{
		printf("argv[%d]:%p\n",i,argv[i]);
	}	

	for(int i = 0; env[i]; ++i)
	{
		printf("env[%d], %p\n",i,env[i]);
	}	
	return 0;
}
