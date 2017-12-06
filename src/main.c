#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>


#define CARDS_PER_PLAYER 13
#define MAX_PALYERS 13
#define CARDS_IN_DECK 13
#define SUIT 4

// #define VERBOSE 1

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
Player getWinner(int players, Card cardsOnDesk[MAX_PALYERS]);

void main(){
    srand( time(NULL) ); // random seed

    int players;
    printf("Enter number of players : ");
    scanf("%d", &players);

    Player playersList[MAX_PALYERS];
    enterPlayersNames(players, playersList);

    Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER];
    Card cardsOnDesk[MAX_PALYERS];

    dealCards(players, allPlayersCards); // deals card to each player
    // each player picks and puts card on the table
    for(int i = 0; i < players; i++){
        showPlayerCards(playersList[i], allPlayersCards);
        Card cardThrown = pickCard(playersList[i], allPlayersCards);
        cardsOnDesk[i] = cardThrown;
    }

    printf("Cards are: ");
    for(int i = 0; i < players; i++){
        printf("%s ", cardsOnDesk[i]);
    }
    println();

    Player winner = getWinner(players, playersList, cardsOnDesk);

    printf("The winner is %s(%d)", winner.name, winner.number);


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

    int i = 0;
    // pic randomly cards and give it to player.
    while(i < CARDS_PER_PLAYER){
        int rNum = rand();
        Card randomCard = newDeck[rNum % 4][rNum % CARDS_IN_DECK];

        if( randomCard.value < 0 ){ continue; } // card is already given

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
    printf("%s (%d), it's your turn.\n", player.name, player.number);
    printf("Hit Space to show cards.\n");
    enterSpace();
    printf("%s,", player.name);
    println();
    printf("%12s","Your cards: ");
    // print player cards
    for(int i = 0; i < CARDS_PER_PLAYER; i++){
        printf("%s %-2d ", allPlayersCards[player.number][i].card,
                            allPlayersCards[player.number][i].value);
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
    do{
        printf("\t(Space to continue)\n");
        scanf("%c", &ch);
    }while(ch != ' ');
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
    }while(uid < 0 || CARDS_PER_PLAYER < uid);

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
        playersList[i] = pl;

        #if defined VERBOSE
        printf("Hello %s!\n", playersList[i].name);
        #endif
    }
}

/**
*   Find the winner from given cards
*/
Player getWinner(int totalPlayers, Card cardsOnDesk[MAX_PALYERS]){
    int winPos = 0;

    for(int i = 1; i < players; i++){
        if( cardsOnDesk[winPos] < cardsOnDesk[i] ){
            winPos = i;
        }
    }

    return winPos;
}
