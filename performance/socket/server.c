#include <stdlib.h>  
#include <sys/types.h>  
#include <stdio.h>  
#include <sys/socket.h>  
#include <linux/in.h>  
#include <string.h>  

#define SENDER_MSG "this is message just for performance test, no. "

int main(int argc, char *argv[])  
{   
	if (argc != 2 ) {
		printf("usage: ./server MSG_NUMBER\n");
		return 1;
	}
	int msg_number = atoi(argv[1]);
    int sfp,nfp; /* 定义两个描述符 */  
    struct sockaddr_in s_add,c_add;  
    int sin_size;  
    unsigned short portnum = 8888; /* 服务端使用端口 */  

    sfp = socket(AF_INET, SOCK_STREAM, 0);  
    if(-1 == sfp)  
    {  
        printf("socket fail\n");  
        return -1;  
    }  

    /* 填充服务器端口地址信息，以便下面使用此地址和端口监听 */  
    bzero(&s_add,sizeof(struct sockaddr_in));  
    s_add.sin_family=AF_INET;  
    s_add.sin_addr.s_addr=htonl(INADDR_ANY); /* 这里地址使用全0，即所有 */  
    s_add.sin_port=htons(portnum);  
    /* 使用bind进行绑定端口 */  
    if(-1 == bind(sfp,(struct sockaddr *)(&s_add), sizeof(struct sockaddr)))  
    {  
        printf("bind fail\n");  
        return -1;  
    }  
    /* 开始监听相应的端口 */  
    if(-1 == listen(sfp,5))  
    {  
        printf("listen fail\n");  
        return -1;  
    }  

    while(1)  
    {  
        sin_size = sizeof(struct sockaddr_in);  
        nfp = accept(sfp, (struct sockaddr *)(&c_add), &sin_size);  
        if(-1 == nfp)  
        {  
            printf("accept fail\n");  
            return -1;  
        }  
        int i = 0;
        char rvbuf[1024];
        for( ; i < msg_number; i++)
        {
            sprintf(rvbuf, "%s%d\n", SENDER_MSG, i);
            if(-1 == write(nfp, rvbuf, strlen(rvbuf)), 0)  
            {  
                printf("write fail\n");  
                return -1;  
            }  
        }
        close(nfp);  
        break;
    }  
    close(sfp);  
    return 0;  
}  
