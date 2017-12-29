#include "game.h"

int pointsToNextRound = 0;

/**
*   Creates new card deck as 2D array. 4 suits(rows) each 13 cards(coloms).
*/
void createNewDeck(Card newDeck[4][CARDS_IN_DECK]){
    // hard coded card deck
    // Card cards[4][CARDS_IN_DECK] = {
    //     {
    //         {"🂲", 2}, {"🂳", 3}, {"🂴", 4}, {"🂵", 5}, {"🂶", 6}, {"🂷", 7}, {"🂸", 8}, {"🂹", 9},
    //         {"🂺", 10}, {"🂻", 11}, {"🂽", 12}, {"🂾", 13}, {"🂱", 14}
    //     },
    //     {
    //         {"🃂", 2}, {"🃃", 3}, {"🃄", 4}, {"🃅", 5}, {"🃆", 6}, {"🃇", 7}, {"🃈", 8}, {"🃉", 9},
    //         {"🃊", 10}, {"🃋", 11}, {"🃍", 12}, {"🃎", 13}, {"🃁", 14}
    //     },
    //     {
    //         {"🃒", 2}, {"🃓", 3}, {"🃔", 4}, {"🃕", 5}, {"🃖", 6}, {"🃗", 7}, {"🃘", 8}, {"🃙", 9},
    //         {"🃚", 10}, {"🃛", 11}, {"🃝", 12}, {"🃞", 13}, {"🃑", 14}
    //     },
    //     {
    //         {"🂢", 2}, {"🂣", 3}, {"🂤", 4}, {"🂥", 5}, {"🂦", 6}, {"🂧", 7}, {"🂨", 8}, {"🂩", 9},
    //         {"🂪", 10}, {"🂫", 11}, {"🂭", 12}, {"🂮", 13}, {"🂡", 14}
    //     }
    // };

    Card cards[4][CARDS_IN_DECK] = {
        {
            {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
            {"10", 10}, {"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14}
        },
        {
            {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
            {"10", 10}, {"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14}
        },
        {
            {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
            {"10", 10}, {"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14}
        },
        {
            {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
            {"10", 10}, {"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14}
        }
    };

    // copy hard coded array to given array
    for(int i = 0; i < 4; i++){
        for(int j = 0; j < CARDS_IN_DECK; j++){
            newDeck[i][j] = cards[i][j];
        }
    }
}

/**
*   Gives random cards to the given player.
*/
void getRandomCards(Card playerDeck[CARDS_PER_PLAYER]){
    // take new deck of cards
    Card newDeck[4][CARDS_IN_DECK];
    createNewDeck(newDeck);
    char suits[4] = {'x', 'x', 'x', 'x'}; // harts, diamonds, club, spades
    int suitLeft = 4;

    int i = 0;
    // pic randomly cards and give it to player.
    while(i < CARDS_PER_PLAYER -suitLeft){
        int rNum = rand();
        Card randomCard = newDeck[rNum % 4][rNum % CARDS_IN_DECK];

        if( randomCard.value == USED_CARD ){ continue; } // card is already given
        // mark unique suits
        if( suits[rNum % 4] == 'x'){
            suits[rNum % 4] = 'v';
            suitLeft--;
        }

        playerDeck[i] = randomCard; // give card to player
        newDeck[rNum % 4][rNum % CARDS_IN_DECK].value = USED_CARD; // mark card in deck as given

        #if defined VERBOSE
        printf("[ %s = %d ] ", playerDeck[i].name, playerDeck[i].value);
        #endif

        i++;
    }
    #if defined VERBOSE
    printf("\n");
    #endif

    if(suitLeft > 0){
        #if defined VERBOSE
        printf("Missing %d suits!\n", suitLeft);
        #endif
        for(int j = 0; j < 4; j++){
            if(suits[j] == 'x'){
                int rNum = rand();
                playerDeck[i] = newDeck[j][rNum % CARDS_IN_DECK]; // give card to player
                newDeck[j][rNum % CARDS_IN_DECK].value = USED_CARD; // mark card in deck as given
                i++;
            }
        }
    }
}

/**
*   gives random cards to the given number of players.
*/
void dealCards(int players, Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]){
    // give card to players
    for(int i = 0; i < players; i++){
        Card playerCards[CARDS_PER_PLAYER];
        getRandomCards(playerCards);
        // copy players cards
        for(int j = 0; j < CARDS_PER_PLAYER; j++){
            allPlayersCards[i][j] = playerCards[j];
        }
    }

    #if defined VERBOSE
    for(int i = 0; i < players; i++){
        printf("\n %d --> ", i);
        for(int j = 0; j < CARDS_PER_PLAYER; j++){
            printf("%s ", allPlayersCards[i][j].name);
        }
    }
    println();
    #endif
}

/**
*   Shows given players cards.
*/
void showPlayerCards(Player player, Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]){
    printf("\n(%d) %s, it's your turn. ", player.id, player.name);
    printf("Hit Space to show cards.\n");
    enterSpace();
    printf("%s,\n", player.name);
    printf("%12s","Your cards: ");
    // print player cards
    for(int i = 0; i < CARDS_PER_PLAYER; i++){
        if( allPlayersCards[player.id][i].value == USED_CARD ){
            printf("%2s   ", "_");
        }else{
            printf("%2s   ", allPlayersCards[player.id][i].name );
        }
    }
    println();
    printf("%12s","UID: ");
    // print index of the card
    for(int i = 0; i < CARDS_PER_PLAYER; i++){
        printf("%2d   ", i);
    }
    println();
}

/**
*   Gives card which player picks.
*/
Card pickCard(Player player, Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]){
    int uid;
    Card pickedCard;
    printf("%s pick a card you would like to use.\n", player.name);

    do{
        printf("\tEnter cards UID: ");
        scanf("%d", &uid);
        // if pick not in range(0 to CARDS_PER_PLAYER) or card not exist. REPEAD
    }while(uid < 0 || CARDS_PER_PLAYER < uid || allPlayersCards[player.id][uid].value == USED_CARD);

    pickedCard = allPlayersCards[player.id][uid];
    allPlayersCards[player.id][uid].value = USED_CARD; // mark as gone(used)
    return pickedCard;
}

/**
*   Enter names for each player.
*/
void enterPlayersNames(int players, Player playersList[MAX_PALYERS]){
    for(int i = 0; i < players; i++){
        char name[20];
        printf("Player (%d) enter your name: ", i);
        scanf("%s", name);
        Player pl;
        strcpy(pl.name, name);
        pl.id = i;
        pl.points = 0;
        playersList[i] = pl;

        #if defined VERBOSE
        printf("Hello %s!\n", playersList[i].name);
        #endif
    }
}

/**
*   Find the winner from given cards
*/
Player getWinner(int totalPlayers, Player playersList[MAX_PALYERS], Card cardsOnDesk[MAX_PALYERS]){
    int points, winPos = 0, hasWinner = 0;
    points = removeDublicates(0, totalPlayers, cardsOnDesk);
    #if defined VERBOSE
    printf("--Points(from duplicates): %d\n", points);
    #endif

    for(int i = 0; i < totalPlayers; i++){
        if( cardsOnDesk[i].value == USED_CARD ){ continue; }
        if( cardsOnDesk[winPos].value < cardsOnDesk[i].value ){
            winPos = i;
            hasWinner = 1;
        }
        points += cardsOnDesk[i].value;
    }

    #if defined VERBOSE
    printf("--Cards on desk: ");
    displayCards(totalPlayers, cardsOnDesk);
    printf("--Points: %d\n", points);
    printf("--Points(from last round): %d\n", pointsToNextRound);
    printf("--%s \n", (hasWinner ? "Has Winner" : "No Winner") );
    #endif

    if( hasWinner ){
        playersList[winPos].points += points + pointsToNextRound;
        pointsToNextRound = 0;
    }else{
        pointsToNextRound = points;
        Player p = {"no", -1, -1};
        return p;
    }

    return playersList[winPos];
}

/**
*   Removes dublicates. Recursive calls
*   returns total points in dublicates
*/
int removeDublicates(int startAt, int totalPlayers, Card cardsOnDesk[MAX_PALYERS]){
    #if defined VERBOSE
    printf("----removeDublicates(startAt:%d, totalPlayers:%d,cardsOnDesk.value:%d)\n", startAt, totalPlayers, cardsOnDesk[startAt].value );
    #endif
    if( startAt == totalPlayers ){ return 0; } // recurcion ending condition
    if( cardsOnDesk[startAt].value == USED_CARD ){
        return removeDublicates(startAt +1, totalPlayers, cardsOnDesk); // skip used cards
    }

    int current = cardsOnDesk[startAt].value;
    int hasDubplicate = 0;

    // check if has dublicate
    for(int i = startAt +1; i < totalPlayers; i++){
        if( current == cardsOnDesk[i].value ){
            cardsOnDesk[i].value = USED_CARD;
            hasDubplicate++;
            #if defined VERBOSE
            printf("----Dublicate-1: [%d](%d)\n", i, current );
            #endif
        }
    }

    if( hasDubplicate ){
        cardsOnDesk[startAt].value = USED_CARD;
        hasDubplicate++;
        #if defined VERBOSE
        printf("----Dublicate-2: %d? (%d)\n", hasDubplicate, current );
        #endif
    }

    #if defined VERBOSE
    printf("----Before return: (hasDubplicate:%d * current:%d = %d)\n", hasDubplicate, current, (hasDubplicate * current) );
    #endif
    return hasDubplicate * current +removeDublicates(startAt +1, totalPlayers, cardsOnDesk);
}

/**
*   displays cards from given deck up to given limit.
*/
void displayCards(int limit, Card deck[100]){
    for(int i = 0; i < limit; i++){
        #if defined VERBOSE
        printf("%s %d  ", deck[i].name, deck[i].value);
        #endif

        #ifndef VERBOSE
        printf("%s  ", deck[i].name);
        #endif
    }
    println();
}

void displayPlayers(int limit, Player list[100]){
    for(int i = 0; i < limit; i++){
        printf("\t%d points - %s(%d)\n", list[i].points, list[i].name, list[i].id);
    }
    println();
}

void exitGame(int round, int totalPlayers, Player playersList[MAX_PALYERS],
                            Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]){
    printf("Do Yo want to save a current game progress?\n");
    int answ = yesNo();
    if( !answ ){ exit(0); }

    printf("Enter game save name: ");
    char fileName[15];
    scanf("%s", fileName);
    saveGame(fileName, round, totalPlayers, playersList, allPlayersCards);
    addLog(fileName);
    exit(0);
}

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
        // write to file:
        fprintf(pFile,"%d\n", round);
        fprintf(pFile,"%d\n", totalPlayers);
        fprintf(pFile,"%d\n", pointsToNextRound);

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
*   Load game. (TODO: if have time brake to the smaler parts)
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
    fscanf(pFile, "%d", &pointsToNextRound);

    for(int player = 0; player < *pTotalPlayers; player++){
        fscanf(pFile, "%d", &playersList[player].id);
        fscanf(pFile, "%s", playersList[player].name);
        fscanf(pFile, "%d", &playersList[player].points);

        for( int card = 0; card < CARDS_PER_PLAYER; card++){
            fscanf(pFile, "%d", &allPlayersCards[player][card].value);

            switch(allPlayersCards[player][card].value){
                case 1: strcpy(allPlayersCards[player][card].name, "1"); break;
                case 2: strcpy(allPlayersCards[player][card].name, "2"); break;
                case 3: strcpy(allPlayersCards[player][card].name, "3"); break;
                case 4: strcpy(allPlayersCards[player][card].name, "4"); break;
                case 5: strcpy(allPlayersCards[player][card].name, "5"); break;
                case 6: strcpy(allPlayersCards[player][card].name, "6"); break;
                case 7: strcpy(allPlayersCards[player][card].name, "7"); break;
                case 8: strcpy(allPlayersCards[player][card].name, "8"); break;
                case 9: strcpy(allPlayersCards[player][card].name, "9"); break;
                case 10: strcpy(allPlayersCards[player][card].name, "10"); break;
                case 11: strcpy(allPlayersCards[player][card].name, "J"); break;
                case 12: strcpy(allPlayersCards[player][card].name, "Q"); break;
                case 13: strcpy(allPlayersCards[player][card].name, "K"); break;
                case 14: strcpy(allPlayersCards[player][card].name, "A"); break;
                default: strcpy(allPlayersCards[player][card].name, "_"); break;
            }
        }
    }

    fclose(pFile);
    return 1;
}
