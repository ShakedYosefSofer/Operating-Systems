#include "myShell.h"
#include "myFunction.h"
// --------------------------------------------------------------------------------------------
int main() {
    welcome();
    while (1) {
        getLocation();
        char *input = getInputFromUser();
        char **arguments = splitArgument(input); // Splitting the input into an array of strings

        // Check if there are less than 3 arguments (when one of them is the command itself)
        if (arguments[2] == NULL) {
            printf("Usage: cp [source_file] [destination_file]\n");
        } else {
            // Call the cp function with the appropriate paths
            cp(arguments[1], arguments[2]);
            // Call the delete function with the original file path
            delete(arguments[1]);
        }

        // Print all arguments
        for (int i = 0; arguments[i] != NULL; i++) {
            puts(arguments[i]);
        }

        // Call the move function with the appropriate paths
        move(arguments);

        // Call the echoAppend function with the appropriate paths
        echoAppend(arguments);

        // Call the read function with the appropriate path
        // read(arguments);

        free(arguments); // Free memory
        free(input); // Free memory
        
        logout(input); // Check logout condition
        break; // Exit the loop
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
