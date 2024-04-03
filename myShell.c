#include "myShell.h"
#include "myFunction.h"
// --------------------------------------------------------------------------------------------



// Function to check if a substring exists within a string
int containsSubstring(char *str, char *needle) {
    int hay_length = strlen(str);
    int needle_length = strlen(needle);
    if (needle_length == 0) return 1; // If the substring to search for is empty, it exists in any string

    int needle_index = 0; // Index for the needle string

    for (int i = 0; i < hay_length; ++i) {
        if (str[i] == needle[needle_index]) {
            needle_index++; // Move to the next character in the needle string
            if (needle_index == needle_length) {
                // Found the full substring
                return 1;
            }
        } else {
            needle_index = 0; // Reset needle index if characters don't match
        }
    }
    return 0; // Substring not found
}



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
else if (strstr(input, "exit") != NULL) {
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
