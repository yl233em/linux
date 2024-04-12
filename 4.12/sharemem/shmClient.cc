#include"shm.hh"

int main()
{
    //创建key
    key_t key = ftok(PATH, PROJ_ID);
    if(key == -1)
    {
        perror("ftok");
        exit(1);
    }
    Log("创建key成功", Debug) << std::endl;
    
    //获取共享内存
    int shmid = shmget(key, SHM_SIZE, 0);
    if(shmid == -1)
    {
        perror("shmget");
        exit(2);
    }
    Log("申请共享内存成功", Debug) << "shmid:" << shmid << std::endl;
    //sleep(10);
    //与共享内存挂接
    char* shmbuffer = (char*)shmat(shmid, nullptr, 0);
    if(*shmbuffer == -1)
    {
        perror("shmat");
        exit(3);
    }
    Log("挂接成功", Debug) << "shmid:" << shmid << std::endl;
    //sleep(10);

    //使用
    int fd = OpenFIFO(FIFO_NAME, WRITE);
    while(true)
    {
        ssize_t s = read(0, shmbuffer, SHM_SIZE-1);
        if(s > 0)
        {
            shmbuffer[s-1] = 0;
            Signal(fd);
            if(strcmp(shmbuffer, "quit") == 0) break;
        }
    }
    CloseFIFO(fd);
    //解除挂接
    int n = shmdt(shmbuffer);
    if(n == -1)
    {
        perror("shmdt");
        exit(4);
    }
    (void)n;
    Log("解除挂接成功", Debug) << "shmid:" << shmid << std::endl;
    //sleep(10);
    return 0;
}