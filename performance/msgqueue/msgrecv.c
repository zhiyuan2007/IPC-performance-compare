#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <errno.h>  
#include <sys/msg.h>  
  
struct msg_st  
{  
    long int msg_type;  
    char text[BUFSIZ];  
};  
  
int main()  
{  
    int running = 1;  
    int msgid = -1;  
    struct msg_st data;  
    long int msgtype = 0; //注意1  
  
    msgid = msgget((key_t)1234, 0666 | IPC_CREAT);  
    if(msgid == -1)  
    {  
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);  
    }  
    int i  = 0;
    while(running)  
    {  
        if(msgrcv(msgid, (void*)&data, BUFSIZ, msgtype, 0) == -1)  
        {  
            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);  
            exit(EXIT_FAILURE);  
        }  
        i++;
        if (i >= 10000000)
            break;
    }  
    //删除消息队列  
    if(msgctl(msgid, IPC_RMID, 0) == -1)  
    {  
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");  
        exit(EXIT_FAILURE);  
    }  
    exit(EXIT_SUCCESS);  
}  
