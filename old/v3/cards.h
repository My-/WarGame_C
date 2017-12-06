

#ifndef CARDS_IN_DECK
#define CARDS_IN_DECK 13
#endif

#define AH "🂱"
#define AD "🃁"
#define AC "🃑"
#define AS "🂡"

// http://www.c4learn.com/c-programming/c-initializing-array-of-structure/
typedef struct Card{
    char card[4];
    char name[5];
    int value;
} Card;

/**
*   Creates card deck as 2D array. 4 suits(rows) each 13 cards(coloms).
*/
void createNewDeck(Card newDeck[4][CARDS_IN_DECK]);
