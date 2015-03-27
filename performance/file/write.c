#include <stdio.h>

#define SENDER_MSG "this is message just for performance test, no. "
int main(int argc, char *argv[])  
{   
	if (argc != 2 ) {
		printf("usage: ./server MSG_NUMBER\n");
		return 1;
	}
	int msg_number = atoi(argv[1]);
    FILE *fp =fopen("test.txt", "w");
    int i = 0;
    for( ; i < msg_number; i++)
        fprintf(fp, "%s%d\n", SENDER_MSG, i);
    fclose(fp);
    return 0;
}
