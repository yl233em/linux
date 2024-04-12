#include"shm.hh"
Init init;
int main()
{
    //创建公共key
    key_t key = ftok(PATH, PROJ_ID);
    assert(key != -1);

    Log("创建key成功", Debug) << std::endl;

    //获取共享内存
    int shmid = shmget(key, SHM_SIZE, IPC_CREAT | IPC_EXCL|0666);
    assert(shmid != -1);
    Log("申请共享内存成功", Debug) << "shmid:" << shmid << std::endl;

    //和共享内存挂接
    char* shmbuffer = (char*)shmat(shmid, nullptr, 0);
    assert(*shmbuffer != -1);
    Log("挂接成功", Debug) << "shmid:" << shmid << std::endl;
    //sleep(10);
    //进行通信

    int fd = OpenFIFO(FIFO_NAME, READ);
    while(true)
    {
        Wait(fd);
        printf("%s\n", shmbuffer);
        if(strcmp(shmbuffer, "quit") == 0) break;
    }

    //解除共享内存挂接
    int n = shmdt(shmbuffer);
    assert(n != -1);
    (void)n;
    Log("解除挂接成功", Debug) << "shmid:" << shmid << std::endl;
    //sleep(10);
    //释放共享内存
    n = shmctl(shmid, IPC_RMID, nullptr);
    assert(n != -1);
    (void)n;
    return 0;
}