#include <stdio.h>  
#include <unistd.h>  
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
    fifo_fd = open(FIFO_NAME, O_RDONLY);  
    printf("Opened named pipe for reading. \n");  
    while(1)  
    {  
        num=read(fifo_fd,buf,1024);  
        if(num == -1)  
        {  
            printf("Error[%d] when reading data into named pipe\n",errno);  
        }  
        else if (num == 0)  
        {
            break;
        }
        else
        {  
            //buf[num] = '\0';  
            //printf("Readed %d chars from pipe:%s\n", num, buf);  
        }  
    }  
    close(fifo_fd);  
    return 0;  
}  
