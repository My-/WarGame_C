#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>

#define CARDS_PER_PLAYER 13
#define MAX_PALYERS 13
#define CARDS_IN_DECK 13
#define SUIT 4

#define VERBOSE 1

// http://www.c4learn.com/c-programming/c-initializing-array-of-structure/
typedef struct Card{
    char name[5];
    int value;
} Card;

/**
*   Creates card deck as 2D array. 4 suits(rows) each 13 cards(coloms).
*/
void createNewDeck(Card newDeck[4][CARDS_IN_DECK]);

/**
*   Gives random cards to player.
*/
void getCards(Card palyerDeck[CARDS_PER_PLAYER]);

void main(){
    srand( time(NULL) ); // random seed

    int palyers;
    printf("Enter number of players: ");
    scanf("%d", &palyers);

    Card cardsOnDesk[MAX_PALYERS];


    Card newDeck[4][CARDS_IN_DECK];
    createNewDeck(newDeck);

    Card playerDeck[CARDS_PER_PLAYER];
    getCards(playerDeck);

    Card playersCards[MAX_PALYERS][CARDS_PER_PLAYER];

    for(int i = 0; i < CARDS_PER_PLAYER; i++){
        printf("[Card: %s = %d] ", playerDeck[i].name, playerDeck[i].value);
    }


    // for(int i = 0; i < SUIT; i++){
    //     printf("\n");
    //     for(int j = 0; j < CARDS_IN_DECK; j++){
    //         printf("[Name: %s, Value: %d] ", newDeck[i][j].name, newDeck[i][j].value);
    //     }
    // }


    int zxc; scanf("%d", &zxc); // Pause
}


/**
*   Creates card deck as 2D array. 4 suits(rows) each 13 cards(coloms).
*/
void createNewDeck(Card newDeck[4][CARDS_IN_DECK]){
    Card cards[CARDS_IN_DECK] = {
        {"2", 2}, {"3", 3}, {"4", 4},
        {"5", 5}, {"6", 6}, {"7", 7},
        {"8", 8}, {"9", 9}, {"10", 10},

        {"Jack", 11}, {"Queen", 12},
        {"King", 13}, {"Ace", 14}
    };

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < CARDS_IN_DECK; j++){
            newDeck[i][j] = cards[j];
        }
    }
}

/**
*   Gives random cards to player.
*/
void getCards(Card playerDeck[CARDS_PER_PLAYER]){
    Card newDeck[4][CARDS_IN_DECK];
    createNewDeck(newDeck);

    for(int i = 0; i < CARDS_PER_PLAYER; i++){
        int rNum = rand();
        playerDeck[i] = newDeck[rNum % 4][rNum % CARDS_IN_DECK];
        #if defined VERBOSE
        printf("[Card: %s = %d] ", playerDeck[i].name, playerDeck[i].value);
        #endif
    }
    printf("\n");

}
