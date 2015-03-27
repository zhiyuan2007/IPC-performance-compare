#include <stdio.h>
#include <stddef.h>
#include <sys/stat.h>
#include <sys/socket.h>
#include <stdio.h>
#include <sys/un.h>
#include <errno.h>

#define CLI_PATH    "/var/tmp/"      /* +5 for pid = 14 chars */

/*
 * Create a client endpoint and connect to a server.
 * Returns fd if all OK, <0 on error.
 */
int cli_conn(const char *name)
{
    int                fd, len, err, rval;
    struct sockaddr_un un;

    /* create a UNIX domain stream socket */
    if ((fd = socket(AF_UNIX, SOCK_STREAM, 0)) < 0)
        return(-1);

    /* fill socket address structure with our address */
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    sprintf(un.sun_path, "%s%05d", CLI_PATH, getpid());
    len = offsetof(struct sockaddr_un, sun_path) + strlen(un.sun_path);

    unlink(un.sun_path);        /* in case it already exists */
    if (bind(fd, (struct sockaddr *)&un, len) < 0) {
        rval = -2;
        goto errout;
    }

    /* fill socket address structure with server's address */
    memset(&un, 0, sizeof(un));
    un.sun_family = AF_UNIX;
    strcpy(un.sun_path, name);
    len = offsetof(struct sockaddr_un, sun_path) + strlen(name);
    if (connect(fd, (struct sockaddr *)&un, len) < 0) {
        rval = -4;
        goto errout;
    }
    return(fd);

errout:
    err = errno;
    printf("close due to error: %d, %s\n", errno, strerror(errno));
    close(fd);
    errno = err;
    return(rval);
}

int main()
{
    const char *file = "foo.sock";
    printf("connect\n");
    int connfd = cli_conn(file);
    if(connfd<0)  
    {  
        printf("Error[%d] when connecting...",errno);  
        return 0;  
    }  
    printf("Begin to recv/send...\n");    
    int i,n,size;  
    char rvbuf[4096];  
    for(i=0;;i++)  
    {  
        size = recv(connfd, rvbuf, 1024, 0);     
        if(size>0)  
        {  
            // rvbuf[size]='\0';  
            //printf("%s\n",rvbuf);  
        }  
        else if (size == 0)
        {
            break;
        }
        else if(size==-1)  
        {  
            printf("Error[%d] when recieving Data:%s.\n",errno,strerror(errno));      
            break;       
        }
  
    }  
    close(connfd);  
    return 0;
}
