#include<stdio.h>
#include<unistd.h>
#include<string.h>

#define NUM 102
int main()
{
	char bar[NUM];
	memset(bar,0,sizeof(bar));
	const char* lable = "\\-|/";
	int cnt = 0;
	while(cnt <= 100)
	{
		printf("[%-100s][%d%%] %c\r",bar,cnt, lable[cnt%4]);
		bar[cnt++] = '#';
		fflush(stdout);
		usleep(300000);
	}
	printf("\n");
	return 0;
}
