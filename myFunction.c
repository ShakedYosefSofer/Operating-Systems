#include "myFunction.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <errno.h>


// בפונקציה הנ"ל קיבלנו את הנתיב ממנו אנחנו מריצים את התוכנית שלנו
//  עליכם לשדרג את הנראות של הנתיב כך ש-בתחילת הנתיב יופיע שם המחשב (כמו בטרמינל המקורי) בסוף יופיע הסימן דולר
//  ולאחר הדולר ניתן אפשרות למשתמש להזין מחרוזת מבלי שנרד שורה.

#define SIZE_BUFF 256


void getLocation()
{
    char location[SIZE_BUFF];
    if (getcwd(location, SIZE_BUFF) == NULL)
        printf("Error\n");
    else
    {
        // קביעת שם המחשב
        char hostname[SIZE_BUFF];
        gethostname(hostname, SIZE_BUFF);

        // הצגת שם המחשב, הנתיב וסימן דולר
        printf("\033[0;31m%s@%s:\033[0m", getenv("USER"), hostname);
        printf("\033[0;34m%s\033[0m", location);
        printf("\033[0;32m$\033[0m\n");
    }
}

char *getInputFromUser()
{
    char ch;
    int size = 1;
    int index = 0;
    char *str = (char *)malloc(size * sizeof(char));
    while ((ch = getchar()) != '\n')
    {
        *(str + index) = ch;
        size++;
        index++;
        str = (char *)realloc(str, size);
    }
    *(str + index) = '\0';
    return str;
}
// עליכם לממש את הפונקציה strtok כלומר שהפונקציה הנ"ל תבצע בדיוק אותו הדבר רק בלי השימוש בפונקציה strtok
char **splitArgument(char *str)
{

    int size = 2;
    int index = 0;
    char **arguments = (char **)malloc(size * sizeof(char *));
    char *subStr = str;

    while (*subStr != '\0')
    {
        // התחלה של כל מחרוזת
        while (*subStr == ' ')
            subStr++;

        // סיום אם הגענו לסוף המחרוזת
        if (*subStr == '\0')
            break;

        // איתור סיום התת-מחרוזת
        char *end = subStr;
        while (*end != ' ' && *end != '\0')
            end++;

        // אחסון התת-מחרוזת במערך המצביעים
        int subStrLen = end - subStr;
        arguments[index] = (char *)malloc((subStrLen + 1) * sizeof(char));
        strncpy(arguments[index], subStr, subStrLen);
        arguments[index][subStrLen] = '\0';

        index++;
        size++;
        arguments = (char **)realloc(arguments, size * sizeof(char *));

        // התקדמות לתחילת התת-מחרוזת הבאה
        subStr = end;
    }

    arguments[index] = NULL; // הוספת NULL לסיום המערך

    return arguments;
}

void logout(char *str) {
    char *token;
    char delimiter[] = " \t\n"; // רווח, טאב, או שורה חדשה משמשים כסיווגים לפצל

    token = strtok(str, delimiter); // פיצול המחרוזת למחרוזות נפרדות

    while (token != NULL) {
        if (strcmp(token, "exit") == 0) { // אם המחרוזת הנוכחית היא "exit"
            printf("Logging out...\n");
            exit(EXIT_SUCCESS);
        }

        token = strtok(NULL, delimiter); // משך הבדיקה לתא הבא במערך המצביעים
    }
}


void cd(char **args) {
    char newPath[1024];
    strcpy(newPath, "");

    // אם המחרוזת הראשונה מתחילה בגרש, שרשר את כל התתי מחרוזות
    if (args[1][0] == '"') {
        for (int i = 1; args[i] != NULL; i++) {
            strcat(newPath, args[i] + 1); // דלג על הגרש הראשון
            strcat(newPath, " "); // הוסף רווח בין כל תת המחרוזות
        }
        // הוסף גרש סופי ותו נולה בסיום הנתיב
        newPath[strlen(newPath) - 1] = '"';
        newPath[strlen(newPath)] = '\0';
    } else {
        strcpy(newPath, args[1]); // אם אין גרש, שלח את התת-מחרוזת הראשונה
    }

    printf("Changing directory to: %s\n", newPath); // פונקציה מסיבות הדגמה
    // פה נכניס את הפקודה המתאימה לשינוי הנתיב בפועל
}

void cp(char *source_path, char *destination_path) {
    FILE *source_file, *destination_file;
    char ch;

    // פתיחת קובץ המקור לקריאה
    source_file = fopen(source_path, "r");
    if (source_file == NULL) {
        printf("Error: Unable to open source file %s\n", source_path);
        return;
    }

    // פתיחת קובץ היעד לכתיבה
    destination_file = fopen(destination_path, "w");
    if (destination_file == NULL) {
        printf("Error: Unable to open destination file %s\n", destination_path);
        fclose(source_file); // סגירת קובץ המקור
        return;
    }

    // העתקת תוכן הקובץ המקורי לקובץ היעד
    while ((ch = fgetc(source_file)) != EOF) {
        fputc(ch, destination_file);
    }

    // סגירת קובץים
    fclose(source_file);
    fclose(destination_file);

    printf("File copied successfully.\n");
}



void delete(char *str) {
    // בדיקה האם הנתיב מכיל רווחים
    if (strchr(str, ' ') != NULL) {
        // הוספת גרשיים מסביב לנתיב כולו
        char temp[strlen(str) + 3]; // +3 לשני הגרשיים והתו '\0'
        sprintf(temp, "\"%s\"", str);
        // מחיקת הקובץ על פי הנתיב המוגדר
        if (remove(temp) == 0) {
            printf("File deleted successfully.\n");
        } else {
            printf("Error: Unable to delete the file.\n");
        }
    } else {
        // אם אין רווחים בנתיב, מחיקה רגילה
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

    if (pipe(pipefd) == -1) {
        perror("pipe");
        return;
    }

    pid = fork();
    if (pid == -1) {
        perror("fork");
        return ;
    } else if (pid == 0) {
        // Child process
        close(pipefd[0]); // Close the read end of the pipe
        dup2(pipefd[1], STDOUT_FILENO); // Redirect stdout to the write end of the pipe
        close(pipefd[1]); // Close the write end of the pipe

        // Execute the first command
        execvp(argv1[0], argv1);
        perror("execvp"); // This line should not be reached if execvp succeeds
        _exit(1);
    } else {
        // Parent process
        close(pipefd[1]); // Close the write end of the pipe
        dup2(pipefd[0], STDIN_FILENO); // Redirect stdin to the read end of the pipe
        close(pipefd[0]); // Close the read end of the pipe

        // Execute the second command
        execvp(argv2[0], argv2);
        perror("execvp"); // This line should not be reached if execvp succeeds
        _exit(1);
    }
}



void move(char **arguments) {
    if (arguments[1] == NULL) {
        printf("mv: missing file operand\n");
        return;
    }

    if (arguments[2] == NULL) {
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
    // אם אחד הפרמטרים או שניהם הם NULL, אין לנו מספיק פרמטרים
    if (args[1] == NULL || args[2] == NULL) {
        printf("Usage: echo >> [file_path] [text_to_append]\n");
        return;
    }

    // פתיחת קובץ להוספת תוכן, אם הקובץ אינו קיים הוא יווצר
    FILE *file = fopen(args[2], "a");
    if (file == NULL) {
        printf("Failed to open file %s\n", args[2]);
        return;
    }

    // מחרוזת עם התוכן שנרצה להוסיף
    char *content = args[3];

    // הוספת התוכן לקובץ
    fprintf(file, "%s\n", content);

    // סגירת הקובץ
    fclose(file);

    printf("Appended \"%s\" to file %s\n", content, args[2]);
}

void echorite(char **arguments) {
    int size = 0;
    while (arguments[size] != NULL) {
        size++;
    }
    FILE *file;

    if ((file = fopen(arguments[size - 1], "w")) == NULL) {
        puts("error");
        return;
    }

    // Write the received string to the file
    for (int i = 1; i < size - 2; i++) {
        fprintf(file, "%s ", arguments[i]);
    }
    fprintf(file, "\n"); // Add a line break

    fclose(file);
}

void read(char **arguments) {
    // בדיקה אם אין ארגומנט ראשון או שיש יותר מארגומנט אחד
    if (arguments[1] == NULL || arguments[2]) {
        puts("Usage: read [file_path]");
        return;
    }

    FILE *file;
    char ch;

    // פתיחת הקובץ לקריאה
    if (!(file = fopen(arguments[1], "r"))) {
        puts("Error: Unable to open file");
        return;
    }

    // קריאת הקובץ והדפסת התוכן שלו למסך
    while ((ch = fgetc(file)) != EOF)
        putchar(ch);

    // סגירת הקובץ
    fclose(file);
}



// בכל שינוי יש לבצע קומיט מתאים העבודה מחייבת עבודה עם גיט.
// ניתן להוסיף פונקציות עזר לתוכנית רק לשים לב שלא מוסיפים את חתימת הפונקציה לקובץ הכותרות


