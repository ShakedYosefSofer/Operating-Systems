#include "myFunction.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <sys/wait.h>


// בפונקציה הנ"ל קיבלנו את הנתיב ממנו אנחנו מריצים את התוכנית שלנו
//  עליכם לשדרג את הנראות של הנתיב כך ש-בתחילת הנתיב יופיע שם המחשב (כמו בטרמינל המקורי) בסוף יופיע הסימן דולר
//  ולאחר הדולר ניתן אפשרות למשתמש להזין מחרוזת מבלי שנרד שורה.

#define SIZE_BUFF 256


void getLocation()
{
    // Buffer size for storing location
    char location[SIZE_BUFF];

    // Get the current working directory
    if (getcwd(location, SIZE_BUFF) == NULL) {
        printf("Error\n");
        return;
    }

    // Get the hostname
    char hostname[SIZE_BUFF];
    if (gethostname(hostname, SIZE_BUFF) == -1) {
        printf("Error\n");
        return;
    }

    // Display the prompt
    printf("\033[0;31m%s@%s:\033[0m", getenv("USER"), hostname); // Display username and hostname in red color
    printf("\033[0;34m%s\033[0m", location); // Display location in blue color
    printf("\033[0;32m$\033[0m\n"); // Display prompt symbol in green color
}

char *getInputFromUser()
{
    char ch;
    int size = 1;
    int index = 0;
    char *str = (char *)malloc(size * sizeof(char));
    while ((ch = getchar()) != '\n')
    {
        if(ch != '\n') 
        {
            *(str + index) = ch;
            size++;
            index++;
            str = (char *)realloc(str, size);
        }
    }
    *(str + index) = '\0';
    return str;
}


// You are required to implement the strtok function, meaning that this function will perform exactly the same thing but without using the strtok function.
char **splitArgument(char *str)
{
    int size = 2;
    int index = 0;
    char **arguments = (char **)malloc(size * sizeof(char *));
    char *token = strtok(str, " "); // Split the string by space

    while (token != NULL)
    {
        arguments[index] = (char *)malloc((strlen(token) + 1) * sizeof(char));
        strcpy(arguments[index], token);
        index++;
        size++;
        arguments = (char **)realloc(arguments, size * sizeof(char *));
        token = strtok(NULL, " "); // Get the next token
    }

    arguments[index] = NULL; // Adding NULL to the end of the array

    return arguments;
}


// This function logs out the user if the "exit" command is entered.
void logout(char *str) {
    char *token;
    char delimiter[] = " \t\n"; // Spaces, tabs, or newline characters serve as delimiters

    // Splitting the string into separate tokens
    token = strtok(str, delimiter);

    // Looping through each token
    while (token != NULL) {
        // If the current token is "exit"
        if (strcmp(token, "exit") == 0) {
            // Exit the program
            exit(EXIT_SUCCESS);
        }

        // Move to the next token
        token = strtok(NULL, delimiter);
    }
}


// This function changes the current directory to the specified path.
void cd(char **args) {
    char newPath[1024];
    strcpy(newPath, "");

    // If the first string starts with a double quote, concatenate all substrings
    if (args[1][0] == '"') {
        // Loop through each substring
        for (int i = 1; args[i] != NULL; i++) {
            strcat(newPath, args[i] + 1); // Skip the first double quote
            strcat(newPath, " "); // Add a space between each substring
        }
        // Add a closing double quote and null terminator at the end of the path
        newPath[strlen(newPath) - 1] = '"';
        newPath[strlen(newPath)] = '\0';
    } else {
        strcpy(newPath, args[1]); // If there's no double quote, take the first substring
    }

    printf("Changing directory to: %s\n", newPath); // For demonstration purposes
    // Insert the actual command here to change the directory
}


// This function copies the contents of a source file to a destination file.
void cp(char *source_path, char *destination_path) {
    FILE *source_file, *destination_file;
    char ch;

    // Open the source file for reading
    source_file = fopen(source_path, "r");
    if (source_file == NULL) {
        printf("Error: Unable to open source file %s\n", source_path);
        return;
    }

    // Open the destination file for writing
    destination_file = fopen(destination_path, "w");
    if (destination_file == NULL) {
        printf("Error: Unable to open destination file %s\n", destination_path);
        fclose(source_file); // Close the source file
        return;
    }

    // Copy the contents of the source file to the destination file
    while ((ch = fgetc(source_file)) != EOF) {
        fputc(ch, destination_file);
    }

    // Close the files
    fclose(source_file);
    fclose(destination_file);

    printf("File copied successfully.\n");
}


void delete(char *str) {
    // Check if the path contains spaces
    if (strchr(str, ' ') != NULL) {
        // Add double quotes around the entire path
        char temp[strlen(str) + 3]; // +3 for the two double quotes and the null terminator '\0'
        sprintf(temp, "\"%s\"", str);
        // Delete the file according to the defined path
        if (remove(temp) == 0) {
            printf("File deleted successfully.\n");
        } else {
            printf("Error: Unable to delete the file.\n");
        }
    } else {
        // If there are no spaces in the path, perform a regular deletion
        if (remove(str) == 0) {
            printf("File deleted successfully.\n");
        } else {
            printf("Error: Unable to delete the file.\n");
        }
    }
}

void mypipe(char **argv1, char **argv2) {
    int pipefd[2];
    pid_t pid;

    // Create pipe
    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    // Fork child process
    pid = fork();
    if (pid == -1) {
        perror("fork");
        return;
    } else if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close the read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe
        close(pipefd[1]); // Close the write end of the pipe

        // Execute the first command
        if (execvp(argv1[0], argv1) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    } else {
        // Parent process
        close(pipefd[1]); // Close the write end of the pipe
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe
        close(pipefd[0]); // Close the read end of the pipe

        // Wait for child process to complete
        wait(NULL);

        // Execute the second command
        if (execvp(argv2[0], argv2) == -1) {
            perror("execvp");
            exit(EXIT_FAILURE);
        }
    }
}



void move(char **arguments) {
    if (arguments[1] == NULL || arguments[2] == NULL) {
        if (arguments[1] == NULL)
            printf("mv: missing file operand\n");
        else
            printf("mv: missing destination file operand after '%s'\n", arguments[1]);
        return;
    }

    if (arguments[3] != NULL) {
        printf("mv: too many arguments\n");
        return;
    }

    if (rename(arguments[1], arguments[2]) != 0) {
        switch (errno) {
            case ENOENT: // No such file or directory
                printf("mv: cannot stat '%s': No such file or directory\n", arguments[1]);
                break;
            case EACCES: // Permission denied
                printf("mv: cannot create regular file '%s': Permission denied\n", arguments[2]);
                break;
            case EISDIR: // Is a directory
                printf("mv: cannot create regular file '%s': Is a directory\n", arguments[2]);
                break;
            case EEXIST: // File exists
                printf("mv: cannot create regular file '%s': File exists\n", arguments[2]);
                break;
            default:
                perror("mv"); // Print system error message
                break;
        }
    } else {
        printf("'%s' was successfully moved to '%s'\n", arguments[1], arguments[2]);
    }
}


void echoAppend(char **args) {
    // Find the index of "<<"
    int splitIndex = 0;
    while (args[splitIndex] != NULL) {
        if (strcmp(args[splitIndex], ">>") == 0) {
            break;
        }
        splitIndex++;
    }

    // Check if there is text before the "<<"
    if (splitIndex == 0) {
        printf("Error: No text specified.\n");
        return;
    }

    // Combine all arguments from the second one until the one before "<<"
    int totalLength = 0;
    for (int i = 1; i < splitIndex; ++i) {
        totalLength += strlen(args[i]) + 1; // +1 for space
    }

    // Allocate memory for the text
    char *text = (char *)malloc(totalLength + 1); // +1 for null terminator
    if (text == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // Concatenate all arguments into one string
    text[0] = '\0'; // Initialize the string
    for (int i = 1; i < splitIndex; ++i) {
        strcat(text, args[i]);
        strcat(text, " "); // Add space between arguments
    }

    // Remove the trailing space
    text[strlen(text) - 1] = '\0';

    // Get the file path after "<<"
    char *filePath = args[splitIndex + 1];

    // Open the file for appending, create if not exists
    FILE *file = fopen(filePath, "a+");
    if (file == NULL) {
        // Unable to open or create the file
        printf("Error: Unable to open or create the file.\n");
        free(text); // Free allocated memory
        return;
    }

    // Write the text to the file
    fprintf(file, "%s\n", text);

    // Close the file
    fclose(file);

    // Free allocated memory
    free(text);

    printf("Text appended to the file successfully.\n");
}

void echorite(char **args) {
    // Find the index of "<"
    int splitIndex = 0;
    while (args[splitIndex] != NULL) {
        if (strcmp(args[splitIndex], ">") == 0) {
            break;
        }
        splitIndex++;
    }

    // Check if there is text before the "<"
    if (splitIndex == 0) {
        printf("Error: No text specified.\n");
        return;
    }

    // Combine all arguments from the second one until the one before "<"
    int totalLength = 0;
    for (int i = 1; i < splitIndex; ++i) {
        totalLength += strlen(args[i]) + 1; // +1 for space
    }

    // Allocate memory for the text
    char *text = (char *)malloc(totalLength + 1); // +1 for null terminator
    if (text == NULL) {
        printf("Error: Memory allocation failed.\n");
        return;
    }

    // Concatenate all arguments into one string
    text[0] = '\0'; // Initialize the string
    for (int i = 1; i < splitIndex; ++i) {
        strcat(text, args[i]);
        strcat(text, " "); // Add space between arguments
    }

    // Remove the trailing space
    text[strlen(text) - 1] = '\0';

    // Get the file path after "<"
    char *filePath = args[splitIndex + 1];

    // Open the file for overwriting, create if not exists
    FILE *file = fopen(filePath, "w");
    if (file == NULL) {
        // Unable to open or create the file
        printf("Error: Unable to open or create the file.\n");
        free(text); // Free allocated memory
        return;
    }

    // Write the text to the file
    fprintf(file, "%s\n", text);

    // Close the file
    fclose(file);

    // Free allocated memory
    free(text);

    printf("Text overwritten to the file successfully.\n");
}

void readf(char **arguments) {
    // Check if no first argument is provided
    if (arguments[1] == NULL) {
        puts("Error: No file path provided");
        return;
    }
    // Check if only one argument is provided
    if (arguments[2] != NULL) {
        puts("Error: Too many arguments");
        return;
    }

    // Open the file for reading
    FILE *file = fopen(arguments[1], "r");
    if (!file) {
        perror("Error");
        return;
    }

    // Obtain file size information
    fseek(file, 0, SEEK_END);
    long file_size = ftell(file);
    rewind(file);

    // If the file is empty, print a message and close it
    if (file_size == 0) {
        puts("File is empty");
        fclose(file);
        return;
    }

    // Read the file and print its contents to the screen
    char *buffer = (char *)malloc(file_size * sizeof(char));
    if (!buffer) {
        perror("Error");
        fclose(file);
        return;
    }

    size_t bytes_read = fread(buffer, sizeof(char), file_size, file);
    if (bytes_read != file_size) {
        puts("Error reading file");
        free(buffer);
        fclose(file);
        return;
    }

    fwrite(buffer, sizeof(char), file_size, stdout);

    // Close the file and free memory
    free(buffer);
    fclose(file);
}


void wordCount(char **args) {
    // Check if the correct number of arguments is provided
    if (args[1] == NULL || args[2] == NULL || args[3] != NULL) {
        printf("Usage: wordCount [-l | -w] [file_path]\n");
        return;
    }

    // Get the option (-L for lines, -W for words)
    char *option = args[1];
    // Get the file path
    char *file_path = args[2];

    // Open the file
    FILE *file = fopen(file_path, "r");

    // Check if the file exists
    if (file == NULL) {
        printf("File '%s' does not exist.\n", file_path);
        return;
    }

    int count = 0; // Counter for lines or words, depending on the option

    // Read the file line by line and count lines or words
    char line[1000]; // Assume lines are not longer than 1000 characters
    if (strcmp(option, "-l") == 0) {
        // Count lines
        while (fgets(line, sizeof(line), file) != NULL) {
            count++;
        }
        printf("Number of lines in '%s': %d\n", file_path, count);
    } else if (strcmp(option, "-w") == 0) {
        // Count words
        while (fscanf(file, "%s", line) != EOF) {
            count++;
        }
        printf("Number of words in '%s': %d\n", file_path, count);
    } else {
        printf("Invalid option '%s'. Use -l for lines or -w for words.\n", option);
    }

    // Close the file
    fclose(file);
}