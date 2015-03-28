#include <stdbool.h>
#include <stdio.h>
#include <stdint.h>
#include <sys/types.h>
#include <fcntl.h>
#include <sys/stat.h>
int get_inode(struct stat *ptr)
{
    return (int)ptr->st_ino;
}
int main(int argc, char **argv)
{
    char filename[1024] = "test.txt";
    bool first = true;
    char line[1024];
    FILE *file;
again:    file = fopen(filename, "r");
    if (!file)
        printf("file not exits\n");
    if (false == first) //first open file, and move file pointer to file-end
    {
        fseek(file, 0, SEEK_END);
        first = true;
    }
    struct stat sbuf;
    if (lstat(filename, &sbuf) == -1)
    {
        printf("read file stat error\n");
    }
    int last_inode = get_inode(&sbuf);
    int ch;
goon:    ch = getc(file);
    int pos = 0;
    int count = 0;
    char strbuf[2048]; 
    while (fgets(strbuf, 2048, file ) != NULL) 
    {
		//printf("%s", strbuf);
    }
    fclose(file);
    //if (feof(file))
    //{
    //    lstat(argv[1], &sbuf);
    //    int new_inode = get_inode(&sbuf);
    //    if (new_inode == last_inode)
    //    {
    //        usleep(100000);
    //        goto goon;
    //    }
    //    else
    //    {
    //        fclose(file);
    //        goto again;
    //    }
    //}

    return 0;
}
