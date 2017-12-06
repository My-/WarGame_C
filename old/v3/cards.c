#include "cards.h"



/**
*   Creates card deck as 2D array. 4 suits(rows) each 13 cards(coloms).
*/
void createNewDeck(Card newDeck[4][CARDS_IN_DECK]){
    Card cards[CARDS_IN_DECK] = {
        {AH, "2", 2}, {AD, "3", 3}, {AC, "4", 4},
        {AS, "5", 5}, {"🂱", "6", 6}, {"🂱", "7", 7},
        {"🂱", "8", 8}, {"🂱", "9", 9}, {"🂱", "10", 10},

        {"🂱", "Jack", 11}, {"🂱", "Queen", 12},
        {"🂱", "King", 13}, {"🂱", "Ace", 14}
    };

    for(int i = 0; i < 4; i++){
        for(int j = 0; j < CARDS_IN_DECK; j++){
            newDeck[i][j] = cards[j];
        }
    }
}
