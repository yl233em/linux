#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <assert.h>

#define NUM 1024
#define SIZE 32
#define SEP " "

//保存完整的命令行字符串
char cmd_line[NUM];

//保存打散之后的命令行字符串
char *g_argv[SIZE];

// 写一个环境变量的buffer，用来测试
char g_myval[64];

#define INPUT_REDIR 1
#define OUTPUT_REDIR 2
#define APPEND_REDIR 3
#define NONE_REDIR 0

int redir_status = NONE_REDIR;

char *CheckRedir(char *start)
{
    assert(start);
    char *end = start + strlen(start) - 1; //ls -a -l\0
    while(end >= start)
    {
        if(*end == '>')
        {
            if(*(end-1) == '>')
            {
                redir_status = APPEND_REDIR;
                *(end-1) = '\0';
                end++;
                break;
            }
            redir_status = OUTPUT_REDIR;
            *end = '\0';
            end++;
            break;
            //ls -a -l>myfile.txt
            //ls -a -l>>myfile.txt
        }
        else if(*end == '<')
        {
            //cat < myfile.txt,输入
            redir_status = INPUT_REDIR;
            *end = '\0';
            end++;
            break;
        }
        else{
            end--;
        }
    }
    if(end >= start)
    {
        return end; //要打开的文件
    }
    else{
        return NULL;
    }
}
// shell 运行原理 ： 通过让子进程执行命令，父进程等待&&解析命令
int main()
{
    extern char**environ;
    //0. 命令行解释器，一定是一个常驻内存的进程，不退出
    while(1)
    {
        //1. 打印出提示信息 
        printf("[root@我的主机 myshell]# ");
        fflush(stdout);
        memset(cmd_line, '\0', sizeof cmd_line);
        //2. 获取用户的键盘输入[输入的是各种指令和选项: "ls -a -l -i"]
        // "ls -a -l>log.txt"
        // "ls -a -l>>log.txt"
        // "ls -a -l<log.txt"
        if(fgets(cmd_line, sizeof cmd_line, stdin) == NULL)
        {
            continue;
        }
        cmd_line[strlen(cmd_line)-1] = '\0';
        // 2.1: 分析是否有重定向, "ls -a -l>log.txt" -> "ls -a -l\0log.txt"
        //"ls -a -l -i\n\0"
        char *sep = CheckRedir(cmd_line);
        //printf("echo: %s\n", cmd_line);
        //3. 命令行字符串解析："ls -a -l -i" -> "ls" "-a" "-i"
        // export myval=105
        g_argv[0] = strtok(cmd_line, SEP); //第一次调用，要传入原始字符串
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
        //?
        while(g_argv[index++] = strtok(NULL, SEP)); //第二次，如果还要解析原始字符串,传入NULL
        if(strcmp(g_argv[0], "export") == 0 && g_argv[1] != NULL)
        {
            strcpy(g_myval, g_argv[1]);
            int ret = putenv(g_myval);
            if(ret == 0) printf("%s export success\n", g_argv[1]);
            //for(int i = 0; environ[i]; i++)
            //    printf("%d: %s\n", i, environ[i]);
            continue;
        }

        //for debug
        //for(index = 0; g_argv[index]; index++)
        //    printf("g_argv[%d]: %s\n", index, g_argv[index]);
        //4.内置命令, 让父进程（shell）自己执行的命令，我们叫做内置命令，内建命令
        if(strcmp(g_argv[0], "cd") == 0) //not child execute, father execute
        {
            if(g_argv[1] != NULL) chdir(g_argv[1]); //cd path, cd ..

            continue;
        }
        //5. fork()
        pid_t id = fork();
        if(id == 0) //child
        {
            if(sep != NULL)
            {
                int fd = -1;
                //说明命令曾经有重定向
                switch(redir_status)
                {
                    case INPUT_REDIR:
                        fd = open(sep, O_RDONLY);
                        dup2(fd, 0);
                        break;
                    case OUTPUT_REDIR:
                        fd = open(sep, O_WRONLY | O_TRUNC | O_CREAT, 0666);
                        dup2(fd, 1);
                        break;
                    case APPEND_REDIR:
                        //TODO
                        fd = open(sep, O_WRONLY | O_APPEND | O_CREAT, 0666);
                        dup2(fd, 1);
                        break;
                    default:
                        printf("bug?\n");
                        break;
                }
            }
           // printf("下面功能让子进程进行的\n");
           // printf("child, MYVAL: %s\n", getenv("MYVAL"));
           // printf("child, PATH: %s\n", getenv("PATH"));
            //cd cmd , current child path
            //execvpe(g_argv[0], g_argv, environ); // ls -a -l -i
            execvp(g_argv[0], g_argv); // ls -a -l -i
            exit(1);
        }
        //father
        int status = 0;
        pid_t ret = waitpid(id, &status, 0);
        if(ret > 0) printf("exit code: %d\n", WEXITSTATUS(status));
    }
}