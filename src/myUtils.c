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

void println(){
    printf("\n");
}

void addLog(char fileName[15]){
    FILE* pFile;
    pFile = fopen(MASTER_FILE, "a");
    // pFile = fopen("autoSave.save", "w");

    if (pFile == NULL){
        printf("The file could not be opened\n"); }
    else{
        fprintf(pFile,"%s\n", fileName);
        fclose(pFile);
    }
}
