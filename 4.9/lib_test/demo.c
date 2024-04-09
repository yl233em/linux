#include"demo.h"

void timep()
{
    time_t t;
    time(&t);
    printf("当前时间秒数%ld\n", t);
}