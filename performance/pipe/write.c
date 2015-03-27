#include <stdio.h>  
#include <unistd.h>  
#include <string.h>  
#include <fcntl.h>   
#include <errno.h>  
#define  FIFO_NAME  "namedpipe"  
int main()  
{  
    int  fifo_fd;  
    int  num;  
    char buf[1024];  
    if(access(FIFO_NAME, F_OK)==  -1)  
    {  
        fifo_fd = mkfifo(FIFO_NAME, 0777);  
    }  
    fifo_fd = open(FIFO_NAME, O_WRONLY);  
    printf("Opened named pipe for writing.\n");  

    int i;  
    for(i=0;i<10000000;i++)  
    {  
        //fgets(buf, 100, stdin);  
        sprintf(buf, "202.173.9.27 www.baidu.com a 1 3:%d\n", i);
        num = strlen(buf);  
        num=write(fifo_fd, buf, num+1);  
        if(num == -1)  
            printf("Error[%d] when writing data into named pipe",errno);   
        //else  
        //    printf("Writed %d chars into named pipe:%s\n", num, buf);  
    }  
    close(fifo_fd);  
    return 0;  
}  
