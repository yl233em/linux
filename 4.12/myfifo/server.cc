#include"road.hh"

int main()
{
    //创建管道文件
    if(mkfifo(ipcPath.c_str(),MODE) < 0)
    {
        perror("mkfifo");
        exit(1);
    }

    Log("创建管道文件成功", Debug) << "step 1" << endl;
    //打开管道文件
    int fd = open(ipcPath.c_str(), O_RDONLY);
    if(fd < 0)
    {
        perror("open");
    }

    Log("打开管道文件成功", Debug) << "step 2" << endl;
    
    //读取客户端数据
    char buffer[SIZE];
    while(true)
    {
        memset(buffer, '\0', sizeof(buffer));
        ssize_t s = read(fd, buffer, sizeof(buffer)-1);

        if(s >0)
        {
            cout << "client say:     " << buffer << endl;
        }
        else if(s == 0)
        {
            cout << "client close, server close too" << endl;
            break;
        }
        else
        {
            perror("read");
            exit(1);
        }

    }

    Log("通信完毕", Debug) << "step 3" <<endl;
    //关闭管道文件
    close(fd);

    Log("关闭管道文件成功", Debug) << "step 4" << endl;

    //删除管道文件
    unlink(ipcPath.c_str());

    Log("删除管道文件成功", Debug) << "step 5" << endl;
    return 0;
}