#include <stdio.h>
int main()
{
    FILE *fp =fopen("test.txt", "w");
    int i = 0;
    char line[1024] = "202.173.9.27 www.baidu.com a 1 3";
    for( ; i < 10000000; i++)
        fprintf(fp, "%s:%d\n", line, i);
    fclose(fp);
    return 0;
}
