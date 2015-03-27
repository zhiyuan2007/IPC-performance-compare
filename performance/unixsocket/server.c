#include <stdio.h>  
#include <sys/stat.h>  
#include <sys/socket.h>  
#include <sys/un.h>  
#include <errno.h>  
#include <stddef.h>  
#include <string.h>  

// the max connection number of the server  
#define MAX_CONNECTION_NUMBER 5  

/* * Create a server endpoint of a connection. * Returns fd if all OK, <0 on error. */  
int unix_socket_listen(const char *servername)  
{   
    int fd;  
    struct sockaddr_un un;   
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)  
    {  
        return(-1);   
    }  
    int len, rval;   
    unlink(servername);               /* in case it already exists */   
    memset(&un, 0, sizeof(un));   
    un.sun_family = AF_UNIX;   
    strcpy(un.sun_path, servername);   
    len = offsetof(struct sockaddr_un, sun_path) + strlen(servername);   
    /* bind the name to the descriptor */   
    if (bind(fd, (struct sockaddr *)&un, len) < 0)  
    {   
        rval = -2;   
    }   
    else  
    {  
        if (listen(fd, MAX_CONNECTION_NUMBER) < 0)      
        {   
            rval =  -3;   
        }  
        else  
        {  
            return fd;  
        }  
    }  
    int err;  
    err = errno;  
    close(fd);   
    errno = err;  
    return rval;    
}  

int unix_socket_accept(int listenfd, uid_t *uidptr)  
{   
    int clifd, len, rval;   
    time_t staletime;   
    struct sockaddr_un un;  
    struct stat statbuf;   
    len = sizeof(un);   
    if ((clifd = accept(listenfd, (struct sockaddr *)&un, &len)) < 0)   
    {  
        return(-1);       
    }  
    /* obtain the client's uid from its calling address */   
    len -= offsetof(struct sockaddr_un, sun_path);  /* len of pathname */  
    un.sun_path[len] = 0; /* null terminate */   
    if (stat(un.sun_path, &statbuf) < 0)   
    {  
        rval = -2;  
    }   
    else  
    {  
        if (S_ISSOCK(statbuf.st_mode) )   
        {   
            if (uidptr != NULL) *uidptr = statbuf.st_uid;    /* return uid of caller */   
            unlink(un.sun_path);       /* we're done with pathname now */   
            return clifd;        
        }   
        else  
        {  
            rval = -3;     /* not a socket */   
        }  
    }  
    int err;  
    err = errno;   
    close(clifd);   
    errno = err;  
    return(rval);  
}  

void unix_socket_close(int fd)  
{  
    close(fd);       
}  

int main(void)  
{   
    int listenfd,connfd;   
    listenfd = unix_socket_listen("foo.sock");  
    if(listenfd<0)  
    {  
        printf("Error[%d] when listening...\n",errno);  
        return 0;  
    }  
    uid_t uid;  
    connfd = unix_socket_accept(listenfd, &uid);  
    unix_socket_close(listenfd);    
    if(connfd<0)  
    {  
        printf("Error[%d] when accepting...\n",errno);  
        return 0;  
    }    
    printf("Begin to recv/send...\n");    
    int i,n,size;  
    char rvbuf[2048];  
    for(i=0;i<10000000;i++)  
    {  
        sprintf(rvbuf, "202.173.9.27 www.baidu.com a 1 3:%d", i);
        size = send(connfd, rvbuf, strlen(rvbuf)+1, 0);  
        if(size>=0)  
        {  
            //printf("Data[%d] Sended:%s.\n",size,rvbuf);  
        }  
        if(size==-1)  
        {  
            printf("Error[%d] when Sending Data:%s.\n",errno,strerror(errno));     
            break;        
        }  
    }  
    unix_socket_close(connfd);  
}  
