#include <stdio.h>
#include "get_next_line.h"

int main()
{
    printf("starting of programme : \n");
    int fd = open("t.txt",O_RDONLY);
    char *str =  get_next_line(fd);
    printf("[%s]",str);
}