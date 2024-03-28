#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char const *argv[])
{
    int filede[2], i;
    char inbuf[100];
    
    if (pipe(filede) < 0)
        return 1;

    write(filede[1], "msg1", 4);
    write(filede[1], "msg2", 4);
    write(filede[1], "msg3", 4);

    for (i = 0; i < 3; i++)
    {
        read(filede[0], inbuf, 4);
        printf("%3s\n", inbuf);
    }
  
    return 0;
}
