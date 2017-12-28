#include "myFile.h"


/**
*   Appends saved game name to end of the log file.
*/
void addLog(char fileName[15]){
    FILE* pFile;
    pFile = fopen(MASTER_FILE, "a");

    if (pFile == NULL){
        printf("The file could not be opened\n"); }
    else{
        fprintf(pFile,"%s\n", fileName);
        fclose(pFile);
    }
}

/**
*   Saves game progress to the file (given name)
*/
void saveGame(char fileName[15], int round, int totalPlayers, Player playersList[MAX_PALYERS],
                                    Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]){
    FILE* pFile;
    strcat(fileName, ".save");
    pFile = fopen(fileName, "w");

    if (pFile == NULL){
        printf("The file could not be opened\n"); }
    else{
        fprintf(pFile,"%d\n", round); // round
        fprintf(pFile,"%d\n", totalPlayers); // total players

        // Player.id, Player.name, Player. points, ...
        for( int player = 0; player < totalPlayers; player++){
            fprintf(pFile,"%d\t%s\t%d", playersList[player].id,
                                        playersList[player].name,
                                        playersList[player].points);
            // Cards
            for( int card = 0; card < CARDS_PER_PLAYER; card++){
                fprintf(pFile,"\t%d", allPlayersCards[player][card].value);
            }
            fprintf(pFile,"\n");
        }
        fclose(pFile);
    }
}


/**
*   Load game part. (TODO: brake to the smaler parts)
*/
int loadGame(int *pRound, int *pTotalPlayers, Player playersList[MAX_PALYERS],
                            Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]){
    // check auto saved game
    FILE* pFile;
    char saves[MAX_SAVES][MAX_FILE_NAME_LENGHT];
    int num_char, hasAutoSave = 0, hasSavedGames = 0;
    char saveName[MAX_FILE_NAME_LENGHT] = AUTO_SAVE;
    strcat(saveName, ".save");

    pFile = fopen(saveName, "r");
    // check for auto saved games( I asume here is no way empty file could exist )
    if (pFile == NULL){ printf("No auto save found.\n"); }
    else{
        hasAutoSave = 1;
        fclose(pFile);
    }

    pFile = fopen(SAVE_LOG, "r");
    // check for saved games( I asume here is no way empty file could exist )
    if (pFile == NULL){
        printf("No preivious saved game found.\n"); }
    else{
        hasSavedGames = 1;
        fclose(pFile);
    }

    // check if we have saves
    if( hasSavedGames || hasAutoSave ){
        printf("Found previaus Saves. Do you want to load game?\n No (n) for new game.\n");
        if( !yesNo() ){ return 0; } // no - dont continue
    }else{
        return 0; // no saves, nothing to load
    }

    // if we here, it means we have saved game and user wants to load it
    printf("Saved game available:\n" );
    if( hasAutoSave ){ printf("\t%s\n", AUTO_SAVE); }

    pFile = fopen(SAVE_LOG, "r");

    if (pFile == NULL){ }
    else{
        while (!feof(pFile)) {
			num_char = fscanf(pFile, "%s", saveName);
			if (num_char > 0){ printf("\t%s\n", saveName); }
		}
        fclose(pFile);
    }

    // take user enter name
    do{
        printf("Enter name of save you want to load( without extension ):\n" );
        scanf("%s", saveName);
        strcat(saveName, ".save");
        pFile = fopen(saveName, "r");
    }while(pFile == NULL);

    // if we here, it means file exist(and asume it has correct data)

    fscanf(pFile, "%d", pRound);
    fscanf(pFile, "%d", pTotalPlayers);

    for(int player = 0; player < *pTotalPlayers; player++){
        fscanf(pFile, "%d", &playersList[player].id);
        fscanf(pFile, "%s", playersList[player].name);
        fscanf(pFile, "%d", &playersList[player].points);

        for( int card = 0; card < CARDS_PER_PLAYER; card++){
            fscanf(pFile, "%d", &allPlayersCards[player][card].value);
        }
    }

    fclose(pFile);
    return 1;
}
