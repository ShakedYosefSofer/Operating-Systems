#include "myShell.h"
#include "myFunction.h"
// --------------------------------------------------------------------------------------------
int main()
{
    welcome();
    while (1)
    {
        getLocation();
        char *input = getInputFromUser();

        // Check if the input is "exit" with or without leading/trailing spaces
        if (strcmp(input, "exit") == 0 || strncmp(input, "exit ", 5) == 0)
            logout(input);

        char **arguments = splitArgument(input);
        if (strcmp(arguments[0], "exit") == 0)
        { // if user enters with space before exit
            free(arguments);
            logout(input);
        }

        int size = sizeArray(arguments);
        int piping = replacePipeWithNull(arguments);
        switch (parseInput(input))
        {
        case 'echo':
            if (size == 1)
                puts(""); // if the user enters only echo
            else if (strcmp(arguments[1], ">") == 0 || strcmp(arguments[1], ">>") == 0)
                puts("-bash: syntax error near unexpected token `newline'");
            else if (strcmp(arguments[size - 2], ">") == 0)
                echorite(arguments); // if the user enters echo > filename
            else if (strcmp(arguments[size - 2], ">>") == 0)
                echoppend(arguments); // if the user enters echo >> filename
            else // if the user enters echo and some words
                echo(arguments);
            break;
        case 'cd':
            cd(arguments);
            break;
        case 'read':
            readfile(arguments);
            break;
        case 'mv':
            move(arguments);
            break;
        case 'wc':
            wordCount(arguments);
            break;
        case 'cp':
            if (size < 3)
                puts("Usage: cp [source_file] [destination_file]");
            else
                cp(arguments[1], arguments[2]);
            break;
        case 'delete':
            delete(arguments);
            break;
        case 'dir':
            get_dir(arguments);
            break;
        case 'pipe':
            handlePiping(arguments);
            break;
        default:
            handleDefault();
            break;
        }

        free(arguments); // Free memory
        free(input);    // Free memory
    }

    return 0;
}
// --------------------------------------------------------------------------------------------

void welcome()
{
    puts("Welcome to my Shell");

    printf("        W   W  EEEEE  L       L         CCCCC   OOO   M     M  EEEEE\n");
    printf("        W   W  E      L       L        C       O   O  MM   MM  E\n");
    printf("        W W W  EEEE   L       L       C       O     O M M M M  EEEE\n");
    printf("        WW WW  E      L       L        C       O   O  M  M  M  E\n");
    printf("         W W   EEEEE  LLLLL   LLLLL     CCCCC   OOO   M     M  EEEEE\n\n");
}

void examplepPipe()
{
    char *argv1[] = {"ls", "-l", NULL}; // Example first command
    char *argv2[] = {"grep", "g", NULL}; // Example second command

    return mypipe(argv1, argv2);
}
