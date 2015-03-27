#include <stdio.h>
#include "zhelpers.h"

int main()
{
        void *context = zmq_ctx_new();
        if (NULL == context)
        {
            printf("aaa\n");
        }
        void *sender = zmq_socket(context, ZMQ_PULL);
        if (NULL == sender)
        {
            printf("aaa\n");
        }
        
        unsigned int i;
        char url[256];
        sprintf(url, "tcp://127.0.0.1:5557");
        zmq_connect(sender, url);
        float  qps = 0.0;
        for(i=0; i<10000000; i++)
        {
            char *temp = s_recv(sender);
            //printf("buff: %s", temp);
        }
        zmq_close(sender);
        zmq_ctx_destroy(context);
}
