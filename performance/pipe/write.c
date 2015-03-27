#include <stdio.h>  
#include <unistd.h>  
#include <string.h>  
#include <fcntl.h>   
#include <errno.h>  
#define  FIFO_NAME  "namedpipe"  
#define SENDER_MSG "this is message just for performance test, no. "
int main(int argc, char *argv[])  
{   
	if (argc != 2 ) {
		printf("usage: ./server MSG_NUMBER\n");
		return 1;
	}
	int msg_number = atoi(argv[1]);
  
    int  fifo_fd;  
    int  num;  
    char buf[1024];  
    if(access(FIFO_NAME, F_OK)==  -1)  
    {  
        fifo_fd = mkfifo(FIFO_NAME, 0777);  
    }  
    fifo_fd = open(FIFO_NAME, O_WRONLY);  

    int i;  
    for(i = 0; i < msg_number; i++)  
    {  
        sprintf(buf, "%s%d\n", SENDER_MSG, i);
        num = write(fifo_fd, buf, strlen(buf));  
        if(num == -1)  
            printf("Error[%d] when writing data into named pipe",errno);   
    }  
    close(fifo_fd);  
    return 0;  
}  
