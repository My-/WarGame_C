#ifndef GAME
#define GAME


#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <time.h>
#include <string.h>
#include "myUtils.h"
// #include "myFile.h"

#define CARDS_PER_PLAYER 13
#define MAX_PALYERS 10
#define CARDS_IN_DECK 13
#define SUIT 4
#define ROUNDS 13
#define USED_CARD 0

#define MAX_SAVES 10
#define MAX_FILE_NAME_LENGHT 15
#define AUTO_SAVE "autoSave"
#define SAVE_LOG "save.log"
#define MASTER_FILE "save.log"

#define SHOW 0
// #define VERBOSE 1


// http://www.c4learn.com/c-programming/c-initializing-array-of-structure/
typedef struct Card{
    char name[5];
    int value;
} Card;

typedef struct Player{
    char name[20];
    int id;
    int points;
} Player;


void createNewDeck(Card newDeck[4][CARDS_IN_DECK]);
void getRandomCards(Card palyerDeck[CARDS_PER_PLAYER]);
void dealCards(int players, Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]);
void showPlayerCards(Player player, Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]);
Card pickCard(Player player, Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]);
void enterPlayersNames(int players, Player playersList[MAX_PALYERS]);
Player getWinner(int players, Player playersList[MAX_PALYERS], Card cardsOnDesk[MAX_PALYERS]);
int removeDublicates(int startAt, int totalPlayers, Card cardsOnDesk[MAX_PALYERS]);
void displayCards(int limit, Card deck[100]);
void displayPlayers(int limit, Player list[100]);
void exitGame(int round, int totalPlayers, Player playersList[MAX_PALYERS],
                            Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]);
void addLog(char fileName[15]);
void saveGame(char fileName[15], int round, int totalPlayers,
                            Player playersList[MAX_PALYERS],
                            Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]);
int loadGame(int *round, int *totalPlayers, Player playersList[MAX_PALYERS],
                            Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]);
int getTotalPoints(int startAt, int totalPlayers, Card cardsOnDesk[MAX_PALYERS]);
void displayWinner(int totalPlayers, Player playersList[MAX_PALYERS]);

#endif
