#include "myUtils.h"

void clearScreen(){
    for(int i = 0; i < 100; i++){ println(); }
}


/**
*   runs until user enters space
*/
void enterSpace(){
    char ch;
    fflush(stdin); // flush buffer

    while ((ch = getchar()) != ' '){
        printf("\t(Space to continue)\n");
        fflush(stdin); // flush buffer
    }
}
