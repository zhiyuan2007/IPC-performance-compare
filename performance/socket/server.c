#include <stdlib.h>  
#include <sys/types.h>  
#include <stdio.h>  
#include <sys/socket.h>  
#include <linux/in.h>  
#include <string.h>  

int main()  
{  
    int sfp,nfp; /* 定义两个描述符 */  
    struct sockaddr_in s_add,c_add;  
    int sin_size;  
    unsigned short portnum=0x8888; /* 服务端使用端口 */  

    printf("Hello,welcome to my server !\r\n");  
    sfp = socket(AF_INET, SOCK_STREAM, 0);  
    if(-1 == sfp)  
    {  
        printf("socket fail ! \r\n");  
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
        printf("bind fail !\r\n");  
        return -1;  
    }  
    /* 开始监听相应的端口 */  
    if(-1 == listen(sfp,5))  
    {  
        printf("listen fail !\r\n");  
        return -1;  
    }  
    printf("listen ok\r\n");  

    while(1)  
    {  
        sin_size = sizeof(struct sockaddr_in);  
        nfp = accept(sfp, (struct sockaddr *)(&c_add), &sin_size);  
        if(-1 == nfp)  
        {  
            printf("accept fail !\r\n");  
            return -1;  
        }  
        int i = 0;
        char rvbuf[1024];
        for( ; i < 10000000; i++)
        {
            sprintf(rvbuf, "202.173.9.27 www.baidu.com a 1 3:%d\n", i);
            if(-1 == write(nfp, rvbuf, strlen(rvbuf)+1), 0)  
            {  
                printf("write fail!\r\n");  
                return -1;  
            }  
        }
        close(nfp);  
        break;

    }  
    close(sfp);  
    return 0;  
}  
