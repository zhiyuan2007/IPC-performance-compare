#include <stdio.h>
#include "zhelpers.h"

int main(int argc, char *argv[])
{
	if (argc != 2 )
	{
		printf("usage ./push msg_nubmer\n");
		return;
	}
	int msg_number = atoi(argv[1]);
	void *context = zmq_ctx_new();
	if (NULL == context)
	{
		printf("create zmq context failed\n");
		return 1;
	}
	void *sender = zmq_socket(context, ZMQ_PUSH);
	if (NULL == sender)
	{
		printf("create zeromq socket failed\n");
		return 1;
	}

	zmq_bind(sender, "tcp://*:5557");

	unsigned int i;
    char temp[256];
	for(i=0; i < msg_number; i++)
	{
		sprintf(temp, "202.173.9.27 www.baidu.com a 1 3:%d\n", i);
		s_send(sender, temp);
	}
	s_send(sender, "exit");
	zmq_close(sender);
	zmq_ctx_destroy(context);
}
