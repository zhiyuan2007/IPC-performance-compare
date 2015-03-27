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
#define SENDER_MSG "this is message just for performance test, no. "

int main(int argc, char *argv[])  
{   
	if (argc != 2 ) {
		printf("usage: ./server MSG_NUMBER\n");
		return 1;
	}
	int msg_number = atoi(argv[1]);
    struct msg_st data;  
  
    int msgid = msgget((key_t)1234, 0666 | IPC_CREAT);  
    if(msgid == -1)  
    {  
        fprintf(stderr, "msgget failed with error: %d\n", errno);  
		return 1;
    }  
  
    int i = 0;
    while( i < msg_number )  
    {  
        data.msg_type = 1;  
        sprintf(data.text, "%s%d\n", SENDER_MSG, i);
        if(msgsnd(msgid, (void*)&data, MAX_TEXT, 0) == -1)  
        {  
            fprintf(stderr, "msgsnd failed\n");  
			return 1;
        }  
        i++;
    }  
    data.msg_type = 1;  
    sprintf(data.text, "%s", "exit");
    msgsnd(msgid, (void*)&data, MAX_TEXT, 0); 
	return 0;
}  
