#include <stdio.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>
#include <unistd.h>
#define SIZE_BUFF 256
char* getInputFromUser();
/**
 * Splits a string into individual tokens based on whitespace.
 * 
 * This function takes a string as input and tokenizes it based on whitespace
 * characters (space, tab, newline). It dynamically allocates memory for an
 * array of strings to store the tokens. The caller is responsible for freeing
 * the memory allocated for the array and its elements when it's no longer needed.
 * 
 * @param input A pointer to the string to be split.
 * 
 * @return A dynamically allocated array of strings (char**) containing the tokens.
 *         The last element of the array is NULL. Returns NULL if input is NULL
 *         or if memory allocation fails.
 * 
 * @note The input string will be modified (tokenized) by this function.
 *       Make sure to use a copy of the original string if preservation
 *       of the original string is required.
 * 
 * @warning The caller is responsible for freeing the memory allocated for
 *          the returned array and its elements using free().
 */
char** splitArgument(char*);
void getLocation();

void logout(char *);
void cd(char **args);
void cp(char *source_path, char *destination_path);
void delete(char *path);
void mypipe(char *argv1[], char *argv2[]);
void move(char **arguments);
void echoAppend(char **arguments);
void echorite(char **arguments);
void readf(char **arguments);
void wordCount(char **arguments);

