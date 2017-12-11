/*
    Writen By:
        Mindaugas Sarskus
    git:
        https://github.com/My-/WarGame_C

    TODO: https://github.com/DaveGamble/cJSON
*/

#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>


#define CARDS_PER_PLAYER 13
#define MAX_PALYERS 10
#define CARDS_IN_DECK 13
#define SUIT 4
#define ROUNDS 13

#define SHOW 0
#define VERBOSE 1


int pointsToNextRound = 0;

// http://www.c4learn.com/c-programming/c-initializing-array-of-structure/
typedef struct Card{
    char card[5];
    int value;
} Card;

typedef struct Player{
    char name[20];
    int number;
    int points;
} Player;


void createNewDeck(Card newDeck[4][CARDS_IN_DECK]);
void getRandomCards(Card palyerDeck[CARDS_PER_PLAYER]);
void dealCards(int players, Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]);
void showPlayerCards(Player player, Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]);
void enterSpace();
void println();
Card pickCard(Player player, Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]);
void enterPlayersNames(int players, Player playersList[MAX_PALYERS]);
Player getWinner(int players, Player playersList[MAX_PALYERS], Card cardsOnDesk[MAX_PALYERS]);
int removeDublicates(int startAt, int totalPlayers, Card cardsOnDesk[MAX_PALYERS]);
void displayCards(int limit, Card deck[100]);
void displayPlayers(int limit, Player list[100]);
void clearScreen();

void main(){
    srand( time(NULL) ); // random seed

    int players;
    do{
        printf("Enter number of players (2-%d): ", MAX_PALYERS);
        scanf("%d", &players);
    }while( players < 2 || MAX_PALYERS < players );

    Player playersList[MAX_PALYERS];
    Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER];
    Card cardsOnDesk[MAX_PALYERS];

    enterPlayersNames(players, playersList);
    dealCards(players, allPlayersCards); // deals card to each player

    // each loop is one round
    for(int round = 0; round < ROUNDS; round++){
        printf("\n================================================================\n" );
        printf("Round %d\n", round +1);

        // each player picks and puts card on the table
        for(int i = 0; i < players; i++){
            showPlayerCards(playersList[i], allPlayersCards);
            Card cardThrown = pickCard(playersList[i], allPlayersCards);
            cardsOnDesk[i] = cardThrown;
        }

        clearScreen();
        printf("Cards on the table are: \n");
        // print card and owner of the card
        for(int i = 0; i < players; i++){
            printf("\t%s - ", playersList[i].name);
            printf("%s (%d)\n", cardsOnDesk[i].card, cardsOnDesk[i].value);
        }
        println();

        Player winner = getWinner(players, playersList, cardsOnDesk);

        printf("At Round %d ", round +1);
        #if defined VERBOSE
        printf("\n-----Winner:{%s}\n", winner.name);
        #endif
        if( winner.number < 0 ){
            printf("Here was no winner..\n");
        }else{
            printf("The winner is %s(%d)\n", winner.name, winner.number);
            printf("%s has %d points.\n", winner.name, winner.points);
        }

        println();
        printf("Leaderboard:\n");
        displayPlayers(players, playersList);

        printf("Continue <space>\n");
        fflush(stdin); // flush buffer
        enterSpace();

    }



    int zxc; scanf("%d", &zxc); // Pause terminal window
}



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
    printf("\n%s(%d), it's your turn. ", player.name, player.number);
    printf("Hit Space to show cards.\n");
    enterSpace();
    printf("%s,\n", player.name);
    printf("%12s","Your cards: ");
    // print player cards
    for(int i = 0; i < CARDS_PER_PLAYER; i++){
        if( allPlayersCards[player.number][i].value < 0 ){
            printf("%s    ", "_");
        }else{
            printf("%s    ", allPlayersCards[player.number][i].card );
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
*   runs until user enters space
*/
void enterSpace(){
    char ch;
    fflush(stdin); // flush buffer

    while ((ch = getchar()) != ' '){
        printf("\t(Space to continue)\n");
        fflush(stdin); // flush buffer
    }

    // do{
    //     printf("\t(Space to continue)\n");
    //     // scanf("%c", &ch);
    //     ch = getchar();
    // }while(ch != ' ');
}

void println(){
    printf("\n");
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
    }while(uid < 0 || CARDS_PER_PLAYER < uid || allPlayersCards[player.number][uid].value < 0);

    pickedCard = allPlayersCards[player.number][uid];
    allPlayersCards[player.number][uid].value = -1; // mark as gone(used)
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
        pl.number = i;
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
        printf("\t%d points - %s(%d)\n", list[i].points, list[i].name, list[i].number);
    }
    println();
}

void clearScreen(){
    for(int i = 0; i < 100; i++){ println(); }
}
