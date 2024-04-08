#include<stdio.h>
#include<stdlib.h>
#include<string.h>
int main()
{
    FILE* fp = fopen("demo", "w");
    const char* s = "linux so easy!\n";
    fwrite(s, sizeof(char), sizeof(char)*(strlen(s)), fp);

    fclose(fp);
    return 0;
}