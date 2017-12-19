#include "game.h"

int pointsToNextRound = 0;

/**
*   Creates new card deck as 2D array. 4 suits(rows) each 13 cards(coloms).
*/
void createNewDeck(Card newDeck[4][CARDS_IN_DECK]){
    // hard coded card deck
    Card cards[4][CARDS_IN_DECK] = {
        {
            {"🂲", 2}, {"🂳", 3}, {"🂴", 4}, {"🂵", 5}, {"🂶", 6}, {"🂷", 7}, {"🂸", 8}, {"🂹", 9},
            {"🂺", 10}, {"🂻", 11}, {"🂽", 12}, {"🂾", 13}, {"🂱", 14}
        },
        {
            {"🃂", 2}, {"🃃", 3}, {"🃄", 4}, {"🃅", 5}, {"🃆", 6}, {"🃇", 7}, {"🃈", 8}, {"🃉", 9},
            {"🃊", 10}, {"🃋", 11}, {"🃍", 12}, {"🃎", 13}, {"🃁", 14}
        },
        {
            {"🃒", 2}, {"🃓", 3}, {"🃔", 4}, {"🃕", 5}, {"🃖", 6}, {"🃗", 7}, {"🃘", 8}, {"🃙", 9},
            {"🃚", 10}, {"🃛", 11}, {"🃝", 12}, {"🃞", 13}, {"🃑", 14}
        },
        {
            {"🂢", 2}, {"🂣", 3}, {"🂤", 4}, {"🂥", 5}, {"🂦", 6}, {"🂧", 7}, {"🂨", 8}, {"🂩", 9},
            {"🂪", 10}, {"🂫", 11}, {"🂭", 12}, {"🂮", 13}, {"🂡", 14}
        }
    };
    // Card cards[4][CARDS_IN_DECK] = {
    //     {
    //         {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
    //         {"10", 10}, {"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14}
    //     },
    //     {
    //         {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
    //         {"10", 10}, {"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14}
    //     },
    //     {
    //         {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
    //         {"10", 10}, {"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14}
    //     },
    //     {
    //         {"2", 2}, {"3", 3}, {"4", 4}, {"5", 5}, {"6", 6}, {"7", 7}, {"8", 8}, {"9", 9},
    //         {"10", 10}, {"J", 11}, {"Q", 12}, {"K", 13}, {"A", 14}
    //     }
    // };

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

        if( randomCard.value < 0 ){ continue; } // card is already given
        // mark unique suits
        if( suits[rNum % 4] == 'x'){
            suits[rNum % 4] = 'v';
            suitLeft--;
        }

        playerDeck[i] = randomCard; // give card to player
        newDeck[rNum % 4][rNum % CARDS_IN_DECK].value = -1; // mark card in deck as given

        #if defined VERBOSE
        printf("[ %s = %d ] ", playerDeck[i].card, playerDeck[i].value);
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
                newDeck[j][rNum % CARDS_IN_DECK].value = -1; // mark card in deck as given
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
            printf("%s ", allPlayersCards[i][j].card);
        }
    }
    println();
    #endif
}

/**
*   Shows given players cards.
*/
void showPlayerCards(Player player, Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]){
    clearScreen();
    printf("\n%s(%d), it's your turn. ", player.name, player.id);
    printf("Hit Space to show cards.\n");
    enterSpace();
    printf("%s,\n", player.name);
    printf("%12s","Your cards: ");
    // print player cards
    for(int i = 0; i < CARDS_PER_PLAYER; i++){
        if( allPlayersCards[player.id][i].value < 0 ){
            printf("%s    ", "_");
        }else{
            printf("%s    ", allPlayersCards[player.id][i].card );
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

// /**
// *   runs until user enters space
// */
// void enterSpace(){
//     char ch;
//     fflush(stdin); // flush buffer
//
//     while ((ch = getchar()) != ' '){
//         printf("\t(Space to continue)\n");
//         fflush(stdin); // flush buffer
//     }
//
//     // do{
//     //     printf("\t(Space to continue)\n");
//     //     // scanf("%c", &ch);
//     //     ch = getchar();
//     // }while(ch != ' ');
// }



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
    }while(uid < 0 || CARDS_PER_PLAYER < uid || allPlayersCards[player.id][uid].value < 0);

    pickedCard = allPlayersCards[player.id][uid];
    allPlayersCards[player.id][uid].value = -1; // mark as gone(used)
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
    displayCards(totalPlayers, cardsOnDesk);
    printf("Points(from duplicates): %d\n", points);
    #endif
    //
    for(int i = 0; i < totalPlayers; i++){
        if( cardsOnDesk[i].value < 0 ){ continue; }
        if( cardsOnDesk[winPos].value < cardsOnDesk[i].value ){
            winPos = i;
            hasWinner = 1;
        }
        points += cardsOnDesk[i].value;
    }

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
    if( startAt == totalPlayers ){ return 0; }
    if( cardsOnDesk[startAt].value < 0){
        return removeDublicates(startAt +1, totalPlayers, cardsOnDesk);
    }

    int current = cardsOnDesk[startAt].value;
    int hasDubplicate = 0;

    for(int i = startAt +1; i < totalPlayers; i++){
        if( current == cardsOnDesk[i].value ){
            cardsOnDesk[i].value = -1;
            hasDubplicate++;
        }
    }

    if( hasDubplicate ){
        cardsOnDesk[startAt].value = -1;
        hasDubplicate++;
    }

    return hasDubplicate *current +removeDublicates(startAt +1, totalPlayers, cardsOnDesk);
}

/**
*   displays cards from given deck up to given limit.
*/
void displayCards(int limit, Card deck[100]){
    for(int i = 0; i < limit; i++){
        #if defined VERBOSE
        printf("%s %d  ", deck[i].card, deck[i].value);
        #endif

        #ifndef VERBOSE
        printf("%s  ", deck[i].card);
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

// void clearScreen(){
//     for(int i = 0; i < 100; i++){ println(); }
// }



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

void saveGame(char fileName[15], int round, int totalPlayers, Player playersList[MAX_PALYERS],
                                    Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]){
    FILE* pFile;
    strcat(fileName, ".save");
    pFile = fopen(fileName, "w");
    // pFile = fopen("autoSave.save", "w");

    if (pFile == NULL){
        printf("The file could not be opened\n"); }
    else{
        fprintf(pFile,"%d\n", round); // round
        fprintf(pFile,"%d\n", totalPlayers); // total players

        // Player.id, Player.name, Player. points, Card.vale, Card.value, Ca..
        for( int player = 0; player < totalPlayers; player++){
            fprintf(pFile,"%d\t%s\t%d", playersList[player].id,
                                        playersList[player].name,
                                        playersList[player].points);

            for( int card = 0; card < CARDS_PER_PLAYER; card++){
                fprintf(pFile,"\t%d", allPlayersCards[player][card].value);
            }
            fprintf(pFile,"\n");
        }
        fclose(pFile);
    }
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
}
