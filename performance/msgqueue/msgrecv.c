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
    struct msg_st data;  
    long int msgtype = 0; //注意1  
  
    int msgid = msgget((key_t)1234, 0666 | IPC_CREAT);  
    if(msgid == -1)  
    {  
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
        exit(EXIT_FAILURE);  
    }  
    int i  = 0;
	int size = 0;
    while(running)  
    {  
        size = msgrcv(msgid, (void*)&data, BUFSIZ, msgtype, 0);
		printf("size %d\n", size);
		if (size == -1)
        {  
            fprintf(stderr, "msgrcv failed with errno: %d\n", errno);  
			return 1;
        }
		if (strcmp(data.text, "exit") == 0 )
			break;
	    printf("data %s", data.text);
    }  
    //删除消息队列  
    if(msgctl(msgid, IPC_RMID, 0) == -1)  
    {  
        fprintf(stderr, "msgctl(IPC_RMID) failed\n");  
	    return 1;
    } 
	return 0;
}  
