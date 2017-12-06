#include <stdio.h>

/**
* give randon number (n) of cards
*/
char *getCards(int n){
    // https://stackoverflow.com/a/5378839
    int *arr =  malloc(sizeof(char) * n);
    for(int i = 0; i < n; i++){
        arr[i] = '0'+ i;
        printf("arr[%d]: %c\n", i, arr[i]);
    }

    return arr;
}

void main(){
    char *cards = getCards(5);

    if(0 == '\0'){ printf("\t\tEqual!!\n"); }
    else{ printf("NOT equal"); }

    int i = 0;
    printf("\n");
    while(cards[i] != '\0'){
        printf("cards[%d]: %c ", i, cards[i]);
        printf("cards[%d]: %c ", i +1, cards[i+1]);
        printf("cards[%d]: %c ", i +2, cards[i+2]);
        i++;
    }

    int zxc; scanf("%d", &zxc); // Pause
}
