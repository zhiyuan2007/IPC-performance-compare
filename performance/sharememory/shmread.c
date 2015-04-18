#include <unistd.h>  
#include <stdlib.h>  
#include <stdio.h>  
#include <sys/sem.h>
#include <sys/shm.h>  
#include "shmdata.h"  
int sem_init() {
    key_t key;
    key = ftok("/home",'a');
    if(key<0)
    {
         perror("ftok error");
         exit(1);
    }
    int semid = semget(key,1,IPC_CREAT|0666);
    if(semid<0)
    {
         perror("semget error");
         exit(1);
    }
	return semid;
}


 int sem_p(int semid) {
    struct sembuf P ={0,-1,SEM_UNDO};
    int ret=semop(semid,&P,1);
    if(ret==-1)
    {
         perror("semop P error");
         exit(1);
    }
	return 0;
}

int sem_v(int semid) {
    struct sembuf V ={0,1,SEM_UNDO};
    int ret=semop(semid,&V,1);
    if(ret==-1)
    {
         perror("semop unlock error");
         exit(1);
    }  
}

int main()  
{  
    int running = 1;//程序是否继续运行的标志  
    void *shm = NULL;//分配的共享内存的原始首地址  
    struct shared_use_st *shared;//指向shm  

	int semid,ret,status;  
	semid = sem_init();
    //创建共享内存  
    int shmid = shmget((key_t)1234, sizeof(struct shared_use_st), 0666|IPC_CREAT);  
    if(shmid == -1)  
    {  
        fprintf(stderr, "shmget failed\n");  
        exit(EXIT_FAILURE);  
    }  
    //将共享内存连接到当前进程的地址空间  
    shm = shmat(shmid, 0, 0);  
    if(shm == (void*)-1)  
    {  
        fprintf(stderr, "shmat failed\n");  
        exit(EXIT_FAILURE);  
    }  
    shared = (struct shared_use_st*)shm;  
    shared->written = 0;  
    while(running)//读取共享内存中的数据  
    {  
        //没有进程向共享内存定数据有数据可读取  
        if(shared->written == 1)  
        {  
            //sleep(rand() % 3);  
            //读取完数据，设置written使共享内存段可写  
            //printf("You wrote: %s", shared->text);  
            shared->written = 0;  
            //输入了end，退出循环（程序）  
            if(strncmp(shared->text, "end", 3) == 0)  
			{
                running = 0;  
				printf("get end comand\n");
			}
			sem_v(semid);
        }  
        else//有其他进程在写数据，不能读取数据  
		{
			sem_p(semid);
            //printf("You wrote: %s", shared->text);  
            shared->written = 0;  
            if(strncmp(shared->text, "end", 3) == 0)  
			{
                running = 0;  
				printf("get end comand\n");
			}

		}
    }  
    //把共享内存从当前进程中分离  
    if(shmdt(shm) == -1)  
    {  
        fprintf(stderr, "shmdt failed\n");  
        exit(EXIT_FAILURE);  
    }  
    //删除共享内存  
    if(shmctl(shmid, IPC_RMID, 0) == -1)  
    {  
        fprintf(stderr, "shmctl(IPC_RMID) failed\n");  
        exit(EXIT_FAILURE);  
    }  
    exit(EXIT_SUCCESS);  
}  
