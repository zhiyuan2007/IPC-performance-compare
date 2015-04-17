#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <string.h>  
#include <sys/shm.h>  
#include "shmdata.h"  

#define SENDER_MSG "this is message just for performance test, no. "
  
int main(int argc, char *argv[])  
{  
	if (argc != 2 ) {
		printf("usage: ./server MSG_NUMBER\n");
		return 1;
	}
	int msg_number = atoi(argv[1]);
  

    int running = 1;  
    void *shm = NULL;  
    struct shared_use_st *shared = NULL;  
    char buffer[BUFSIZ + 1];//用于保存输入的文本  
    int shmid;  
    //创建共享内存  
    shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);  
    if(shmid == -1)  
    {  
        fprintf(stderr, "shmget failed\n");  
        exit(EXIT_FAILURE);  
    }  
    //将共享内存连接到当前进程的地址空间  
    shm = shmat(shmid, (void*)0, 0);  
    if(shm == (void*)-1)  
    {  
        fprintf(stderr, "shmat failed\n");  
        exit(EXIT_FAILURE);  
    }  
    //设置共享内存  
    shared = (struct shared_use_st*)shm;  
    int i = 0;
    while(i < msg_number)//向共享内存中写数据  
    {  
        //数据还没有被读取，则等待数据被读取,不能向共享内存中写入文本  
        while(shared->written == 1)  
        {  
            usleep(1);  
            //printf("Waiting...\n");  
        }  
        //向共享内存中写入数据  
        //printf("Enter some text: ");  
        //fgets(buffer, BUFSIZ, stdin);  
        sprintf(buffer, "%s%d\n", SENDER_MSG, i);
        strncpy(shared->text, buffer, strlen(buffer)+1);  
        //写完数据，设置written使共享内存段可读  
        shared->written = 1;  
        //输入了end，退出循环（程序）  
        if(strncmp(buffer, "end", 3) == 0)  
            running = 0;  
        i++;
    }  
        sprintf(buffer, "end");
        strncpy(shared->text, buffer, strlen(buffer)+1);  
        //写完数据，设置written使共享内存段可读  
        shared->written = 1;  
    //把共享内存从当前进程中分离  
    if(shmdt(shm) == -1)  
    {  
        fprintf(stderr, "shmdt failed\n");  
        exit(EXIT_FAILURE);  
    }  
    sleep(2);  
    exit(EXIT_SUCCESS);  
}
