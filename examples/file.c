#include<stdio.h>
#include<stdlib.h>


void main(){

	FILE* filep;
	int a = 12;
	int c = 120;
	int input;
	int num_char;

	filep = fopen("studentGrade.txt", "w");

	if (filep == NULL){
		printf("The file could not be opened\n"); }
    else{
		fprintf(filep,"%d\n", a);
		fprintf(filep,"%d\n", c);
		fclose(filep);
    }


	filep = fopen("studentGrade.txt", "a");

	 a = -1000;
	 c = -1200;

	if (filep == NULL) {
		printf("The file could not be opened\n");
    else {
		fprintf(filep, "%d\n", a);
		fprintf(filep, "%d\n", c);
		fclose(filep);
    }

	filep = fopen("studentGrade.txt", "r");

	if (filep == NULL) {
		printf("The file cannot be opened\n"); }
    else {
		while (!feof(filep)) {
			num_char = fscanf(filep, "%d", &input);
			if (num_char > 0){ printf("Input: %d\n", input); }
		}
	}
    
}
