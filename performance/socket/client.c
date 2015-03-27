#include <stdlib.h>  
#include <sys/types.h>  
#include <stdio.h>  
#include <sys/socket.h>  
#include <linux/in.h>  
#include <string.h>  

int main()  
{  
    int cfd; /* 文件描述符 */  
    int recbytes;  
    int sin_size;  
    char buffer[1024]={0};    /* 接受缓冲区 */  
    struct sockaddr_in s_add,c_add; /* 存储服务端和本端的ip、端口等信息结构体 */  
    unsigned short portnum=0x8888;  /* 服务端使用的通信端口，可以更改，需和服务端相同 */  

    printf("Hello,welcome to client !\r\n");  
    /* 建立socket 使用因特网，TCP流传输 */  
    cfd = socket(AF_INET, SOCK_STREAM, 0);  
    if(-1 == cfd)  
    {  
        printf("socket fail ! \r\n");  
        return -1;  
    }  
    /* 构造服务器端的ip和端口信息，具体结构体可以查资料 */  
    bzero(&s_add,sizeof(struct sockaddr_in));  
    s_add.sin_family=AF_INET;  
    s_add.sin_addr.s_addr= inet_addr("127.0.0.1"); /* ip转换为4字节整形，使用时需要根据服务端ip进行更改 */  
    s_add.sin_port=htons(portnum); 

    if(-1 == connect(cfd,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))  
    {  
        printf("connect fail !\r\n");  
        return -1;  
    }  
    int i = 0;
    for (; ; i++)
    {
        int size1 = (recbytes = recv(cfd, buffer, 1024, 0));  
        if (size1 < 0)
        {  
            printf("read data fail !\r\n");  
            return -1;  
        }  
        else if (size1 == 0)
        {
            break;
        }
    }
    close(cfd);  
    return 0;  
} 
