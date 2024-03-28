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



// בכל שינוי יש לבצע קומיט מתאים העבודה מחייבת עבודה עם גיט.
// ניתן להוסיף פונקציות עזר לתוכנית רק לשים לב שלא מוסיפים את חתימת הפונקציה לקובץ הכותרות
