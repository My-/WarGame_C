#include "myUtils.h"


/**
*   Clears sctrean in terminal.
*/
void clearScreen(){
    for(int i = 0; i < 100; i++){ println(); }
}


/**
*   Runs until user enters space
*/
void enterSpace(){
    char ch;
    fflush(stdin); // flush buffer

    while ((ch = getchar()) != ' '){
        printf("\t(Space to continue)\n");
        fflush(stdin); // flush buffer
    }
}

/**
*   Adds new line
*/
void println(){
    printf("\n");
}

/**
*   Ask user to enter Yes or No
*   Returns:
*       1 if Yes
*       0 if No
*/
int yesNo(){
    char ch;

    while(1){
        printf("(Yes/No)\n");
        ch = getchar();

        switch (ch) {
            case 'y':
            case 'Y':
                return 1;
            case 'n':
            case 'N':
                return 0;
        }
    }
}
