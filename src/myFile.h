#ifndef MY_UTILS
#define MY_UTILS

#include <stdio.h>
#include "game.h"


#define MASTER_FILE "save.log"


void addLog(char fileName[15]);
void saveGame(char fileName[15], int round, int totalPlayers,
                            Player playersList[MAX_PALYERS],
                            Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]);
int loadGame(int *round, int *totalPlayers, Player playersList[MAX_PALYERS],
                            Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER]);

#endif
