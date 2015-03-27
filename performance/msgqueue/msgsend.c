#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/msg.h>  
#include <errno.h>  
  
#define MAX_TEXT 512  
struct msg_st  
{  
    long int msg_type;  
    char text[MAX_TEXT];  
};  
  
int main()  
{  
    int running = 1;  
    struct msg_st data;  
    int msgid = -1;  
  
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);  
    if(msgid == -1)  
    {  
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);  
    }  
  
    int i  = 0;
    while( i < 10000000)  
    {  
        data.msg_type = 1;  
        sprintf(data.text, "202.173.9.27 www.baidu.com a 1 3:%d\n", i);
        if(msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1)  
        {  
            fprintf(stderr, "msgsnd failed\n");  
            exit(EXIT_FAILURE);  
        }  
        i++;
    }  
    exit(EXIT_SUCCESS);  
}  
