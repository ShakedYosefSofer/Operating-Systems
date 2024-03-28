#include "myFunction.h"
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>


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





// בכל שינוי יש לבצע קומיט מתאים העבודה מחייבת עבודה עם גיט.
// ניתן להוסיף פונקציות עזר לתוכנית רק לשים לב שלא מוסיפים את חתימת הפונקציה לקובץ הכותרות


