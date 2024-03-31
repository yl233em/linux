#include<stdio.h>

int AddToTop(int top)
{
	int i = 1;
	int result = 0;
	while(i < top)
	{
		result += i;
		++i;
	}
	return result;
}


int main()
{
	int top = 100;
	int result = AddToTop(top);
	printf("%d\n", result);
	return 0;
}
