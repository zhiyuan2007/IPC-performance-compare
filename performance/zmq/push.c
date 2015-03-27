#include <stdio.h>
#include "zhelpers.h"

int main()
{
        void *context = zmq_ctx_new();
        if (NULL == context)
        {
            printf("aaa\n");
        }
        void *sender = zmq_socket(context, ZMQ_PUSH);
        if (NULL == sender)
        {
            printf("aaa\n");
        }
        
        unsigned int i;
        char url[256];
        sprintf(url, "tcp://*:5557");
        zmq_bind(sender, url);
        for(i=0; i < 10000000; i++)
        {
            char temp[256];
            sprintf(temp, "202.173.9.27 www.baidu.com a 1 3:%d\n", i);
            s_send(sender, temp);
        }
        zmq_close(sender);
        zmq_ctx_destroy(context);
}
