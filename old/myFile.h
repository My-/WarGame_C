#ifndef MY_FILE
#define MY_FILE

#include <stdio.h>
#include <string.h>
#include "game.h"
#include "myUtils.h"


#define MASTER_FILE "save.log"


void addLog(char fileName[15]);
void saveGame(char fileName[15], int round, int totalPlayers,
                            Player playersList[MAX_PALYERS],
                            Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]);
int loadGame(int *round, int *totalPlayers, Player playersList[MAX_PALYERS],
                            Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]);

#endif
