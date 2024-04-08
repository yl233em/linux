#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/wait.h>
#include<sys/types.h>

#define NUM 1024
#define SIZE 32
#define SEP " "

char cmd_line[NUM];
char *g_argv[SIZE];

int main()
{
	while(1)
	{
		printf("[root@loaclhost myshell]# ");
		fflush(stdout);
		memset(cmd_line, '\0', sizeof cmd_line);

		if(fgets(cmd_line, sizeof cmd_line, stdin) == NULL)
		{
			continue;
		}

		cmd_line[strlen(cmd_line)-1] = '\0';
		g_argv[0] = strtok(cmd_line, SEP);

		int index = 1;
		if(strcmp(g_argv[0], "ls") == 0)
		{
			g_argv[index++] = "--color=auto";
		}
		if(strcmp(g_argv[0], "ll") == 0)
		{
			g_argv[0] = "ls";
			g_argv[index++] = "-l";
			g_argv[index++] = "--color=auto";


		}

		while(g_argv[index++] = strtok(NULL, SEP));
		
		if(strcmp(g_argv[0], "cd") == 0)
		{
			if(g_argv[1]!= NULL) chdir(g_argv[1]);

			continue;
		}

		pid_t id = fork();

		if(id == 0)
		{
			printf("下面功能是子进程执行\n");

			execvp(g_argv[0],g_argv);
			exit(1);
		}

		int status = 0;

		pid_t ret = waitpid(-1, &status, 0);
		if(ret > 0) printf("exit code: %d\n",WEXITSTATUS(status));

	}
}
