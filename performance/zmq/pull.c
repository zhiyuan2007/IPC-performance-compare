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
	for(i=0; ; i++)
	{
		char *temp = s_recv(sender);
		if (strcmp(temp, "exit") == 0)
			break;
		//printf("buff: %s", temp);
	}
	zmq_close(sender);
	zmq_ctx_destroy(context);
}
