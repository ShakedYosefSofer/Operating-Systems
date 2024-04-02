#include "myShell.h"
#include "myFunction.h"



// Function to check if a substring exists within a string
int containsSubstring(const char *haystack, const char *needle) {
    int hay_length = strlen(haystack);
    int needle_length = strlen(needle);
    if (needle_length == 0) return 1; // If the substring to search for is empty, it exists in any string
    if (hay_length < needle_length) return 0; // If the substring to search for is longer than the string being checked, it cannot exist in it

    for (int i = 0; i <= hay_length - needle_length; ++i) {
        if (strncmp(haystack + i, needle, needle_length) == 0) {
            return 1; // Substring found
        }
    }
    return 0; // Substring not found
}




// --------------------------------------------------------------------------------------------

int main() {
    welcome();
    while (1) {
        getLocation(); // show path
        char *input = getInputFromUser(); // get input from user
        char **arguments = splitArgument(input); // Splitting the input into an array of strings
        printf("input: %s\n", input); 
        printf("arguments[0]: %s\n", arguments[0]);
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


    printf("--------------------------------------------\n");
    printf("arguments[0]: %s\n", arguments[0]);
    printf("arguments[1]: %s\n", arguments[1]);
    printf("--------------------------------------------\n");


    delete(arguments[1]);
}
else if (strcmp(input, "read") == 0) {
    printf("Usage: cat [file]\n");
    readf(arguments );
}
else if (strcmp(input, "wc") == 0) {
    printf("Usage: wc [file]\n");
    wordCount(arguments);
}
else if (containsSubstring(input, "exit")) {
    printf("Usage: logout\n");
    logout(input);
}

else if (strcmp(input, "cd") == 0) {
    printf("Usage: cd [directory]\n");
    cd(arguments);
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