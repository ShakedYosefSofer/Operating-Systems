#include "myShell.h"
#include "myFunction.h"
// --------------------------------------------------------------------------------------------
int main() {
    welcome();
    while (1) {
        getLocation();
        char *input = getInputFromUser();
        char **arguments = splitArgument(input); // פיצול הקלט למערך של מחרוזות

        // בדיקה אם ישנם פחות מ-3 ארגומנטים (כאשר אחד מהם הוא הפקודה עצמה)
        if (arguments[2] == NULL) {
            printf("Usage: cp [source_file] [destination_file]\n");
        } else {
            // קריאה לפונקציה cp עם הנתיבים המתאימים
            cp(arguments[1], arguments[2]);
            // קריאה לפונקציה delete עם נתיב הקובץ המקורי
            delete(arguments[1]);
        }

        // הדפסת כל הארגומנטים
        for (int i = 0; arguments[i] != NULL; i++) {
            puts(arguments[i]);
        }

        free(arguments); // שחרור זיכרון
        free(input); // שחרור זיכרון
        
        logout(input); // בדיקת התנאי להתנתקות
        break; // יציאה מהלולאה
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

