#include <stdio.h>  
#include <unistd.h>  
#include <fcntl.h>   
#include <errno.h>  
#include "../util.h"
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
    while(1)  
    {  
        num = readline(fifo_fd, buf, 1024);  
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
            printf("%s", buf);  
        }  
    }  
    close(fifo_fd);  
    return 0;  
}  
