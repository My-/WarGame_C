#include <stdio.h>


struct Card{
    char name;
    int value;
};

/**
* give randon number (n) of cards
*/
void getCards(char deck[], int n){
    for(int i = 0; i < n; i++){
        deck[i] =  i+ '0';
        printf("arr[%d]: %c\n", i, deck[i]);
    }
}

void main(){
    char cards[5];
    getCards(cards, 5);

    if(0 == '\0'){ printf("\t\tEqual!!\n"); }
    else{ printf("NOT equal"); }

    int i = 0;
    printf("\n");
    while(i < 5){
        printf("cards[%d]: %c ", i, cards[i]);
        // printf("cards[%d]: %c ", i +1, cards[i+1]);
        // printf("cards[%d]: %c ", i +2, cards[i+2]);
        i++;
    }

    int zxc; scanf("%d", &zxc); // Pause
}
