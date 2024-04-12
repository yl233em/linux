#pragma once
#include <iostream>
#include <cassert>
#include <string>
#include <cstring>
#include <cstdio>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <sys/ipc.h>
#include <sys/shm.h>
#include "Log.hh"

#define PATH "/home/yl/code"
#define PROJ_ID 0x66
#define SHM_SIZE 4096 // 最好是页的整数倍：4096*n
#define FIFO_NAME "./fifo"

class Init
{
public:
    Init()
    {
        umask(0);
        int n = mkfifo(FIFO_NAME, 0666);
        if (n == 0)
        {
            Log("管道文件创建成功", Debug) << std::endl;
        }
    }
    ~Init()
    {
        unlink(FIFO_NAME);
        Log("管道文件删除成功", Debug) << std::endl;
    }
};

#define WRITE O_WRONLY
#define READ O_RDONLY
int OpenFIFO(std::string pathname, int flag)
{
    int fd = open(pathname.c_str(), flag);
    assert(fd >=0);
    return fd;
}

void Wait(int fd)
{
    Log("等待中...",Notice) << "\n";
    uint32_t temp = 0;
    ssize_t s = read(fd, &temp, sizeof(uint32_t));
    assert(s == sizeof(uint32_t));
    (void) s;
}

void Signal(int fd)
{
    uint32_t temp = 1;
    ssize_t s = write(fd,&temp,sizeof(uint32_t));
    assert(s == sizeof(uint32_t));
    (void)s;
    Log("唤醒中...", Notice) << "\n";
}

void CloseFIFO(int fd)
{
    close(fd);
}