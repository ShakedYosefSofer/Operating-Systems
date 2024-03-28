#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/wait.h>
int main(int argc, char *argv[])
{
    // ls -l | grep C
    for (int i = 0; i < argc; i++)
    {
        puts(argv[i]);
    }

    char *argv1[] = {argv[1], argv[2], NULL};
    char *argv2[] = {argv[3], argv[4], NULL};
    int fildes[2];
    if (fork() == 0)
    {
        pipe(fildes);
        if (fork() == 0)
        {
            /* first component of command line */
            close(STDOUT_FILENO);
            dup(fildes[1]);
            close(fildes[1]);
            close(fildes[0]);
            execvp(argv1[0], argv1);
        }
        /* 2nd command component of command line */
        close(STDIN_FILENO);
        dup(fildes[0]);
        close(fildes[0]);
        close(fildes[1]);
        /* standard input now comes from pipe */
        execvp(argv2[0], argv2);
    }
    wait(NULL);
    return 0;
}
