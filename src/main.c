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

#include "myUtils.h"
#include "game.h"

void main(){
    srand( time(NULL) ); // random seed

    int round = 0;
    int totalPlayers;
    int isLoaded = 0;
    Player playersList[MAX_PALYERS];
    Card allPlayersCards[MAX_PALYERS][CARDS_PER_PLAYER];
    Card cardsOnDesk[MAX_PALYERS];

    isLoaded = loadGame(&round, &totalPlayers, playersList, allPlayersCards);
    if( isLoaded ){ printf("Game Loaded!"); }
    else{

        do{
            printf("Enter number of players (2-%d): ", MAX_PALYERS);
            scanf("%d", &totalPlayers);
        }while( totalPlayers < 2 || MAX_PALYERS < totalPlayers );

        enterPlayersNames(totalPlayers, playersList);
        dealCards(totalPlayers, allPlayersCards); // deals card to each player
    }

    // each loop is one round
    for(  ; round < ROUNDS; round++){ // Why not while loop? I like increase variable here
        printf("\n================================================================\n" );
        printf("Round %d\n", round +1);

        // each player picks and puts card on the table
        for(int i = 0; i < totalPlayers; i++){
            showPlayerCards(playersList[i], allPlayersCards);
            Card cardThrown = pickCard(playersList[i], allPlayersCards);
            cardsOnDesk[i] = cardThrown;
        }

        clearScreen();
        printf("Cards on the table are: \n");
        // print card and owner of the card
        for(int i = 0; i < totalPlayers; i++){
            printf("\t%s - ", playersList[i].name);
            printf("%s (%d)\n", cardsOnDesk[i].name, cardsOnDesk[i].value);
        }
        println();

        Player winner = getWinner(totalPlayers, playersList, cardsOnDesk);

        printf("At Round %d ", round +1);
        if( winner.id < 0 ){
            printf("Here was no winner..\n");
        }else{
            printf("The winner is %s(%d)\n", winner.name, winner.id);
            printf("%s has %d points.\n", winner.name, winner.points);
            playersList[winner.id].points = winner.points;
        }

        println();
        printf("Leaderboard:\n");
        displayPlayers(totalPlayers, playersList);

        // auto save
        char autoSave[15] = "autoSave";
        saveGame(autoSave, round, totalPlayers, playersList, allPlayersCards);

        printf("Continue < Enter >\n");
        printf("Exit < x + Enter >\n");

        char input;
        int invalid = 1;
        do{
            input = getchar();
            switch(input){ // uses swich fall trough
                case 'C':
                case 'c':
                case 'X':
                case 'x':
                    input = tolower(input);
                    invalid = 0;
                    break;
                default:
                    printf("Enter <eXit (x)> or <Continue (c)> \n");
            }
        }while(invalid);

        if( input == 'x'){
            exitGame(round, totalPlayers, playersList, allPlayersCards); }

    }// for round loop



    int zxc; scanf("%d", &zxc); // Pause terminal window
}// main()
