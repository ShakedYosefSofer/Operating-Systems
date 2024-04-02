#include "myShell.h"
#include "myFunction.h"
// --------------------------------------------------------------------------------------------
int main() {
    welcome();
    while (1) {
        getLocation(); // show path
        char *input = getInputFromUser(); // get input from user
        char **arguments = splitArgument(input); // Splitting the input into an array of strings
        printf("input: %s\n", input); 
        printf("arguments[1]: %s\n", arguments[1]);
    
 if (strcmp(input, "cp") == 0) {
    printf("Usage: cp [source_file] [destination_file]\n");
    cp(arguments[1], arguments[2]);
}
else if (strcmp(input, "mv") == 0) {
    printf("Usage: mv [source_file] [destination_file]\n");
    move(arguments);
}
else if (strcmp(input, "echo") == 0) {
    printf("Usage: echo [text] [destination_file]\n");
    echoAppend(arguments);
}
else if (strcmp(input, "rm") == 0) {
    printf("Usage: rm [file]\n");
    delete(arguments[1]);
}
else if (strcmp(input, "read") == 0) {
    printf("Usage: cat [file]\n");
    readf(arguments
    );
}
else if (strcmp(input, "wc") == 0) {
    printf("Usage: wc [file]\n");
    wordCount(arguments);
}
else if (strcmp(input, "exit") == 0) {
    printf("Usage: logout\n");
    logout(input);
}
else if (strcmp(input, "pipe") == 0) {
    printf("Usage: pipe [command1] [command2]\n");
    mypipe(arguments, arguments);
}
   
    
        free(arguments); // Free memory
        free(input); // Free memory
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
