#include"road.hh"

int main()
{
    //打开管道文件
    int fd = open(ipcPath.c_str(), O_WRONLY);
    if(fd < 0)
    {
        perror("open");
        exit(1);
    }
    Log("打开管道文件成功", Debug) << "step 1" << endl;

    //向服务端发送数据
    string msg;
    while(true)
    {
        cout << "输入要发送的信息>>>";
        std::getline(std::cin, msg);
        write(fd, msg.c_str(),msg.size());
    }

    //关闭管道文件
    close(fd);

    return 0;
}