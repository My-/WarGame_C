#include<stdio.h>
#include<string.h>

void main(){
	char namesofweek[7][20];
	char string1[40];
	char string2[40];
	int number;
	int length;
	int compare;
	int i;
	char Months[12][20] = { "Jan","Feb","Mar","Apr","May","June","July","Aug","Sept","Oct","Nov","Dec" };

	printf("Please enter a string\n");
	scanf("%s", string1);
	printf("The first string is %s\n", string1);


	printf("Please enter a string\n");
	scanf("%s", string2);
	printf("The second string is %s\n", string2);


	printf("Please enter a number\n");
	scanf("%d", &number);
	printf("The number is %d\n", number);

	length = strlen(string1);

	printf("The length of string1 is: %d\n", length);

	printf("The length of string2 is: %d\n", strlen(string2));

	compare = strcmp(string1, string2);

	if (compare == 0) {
		printf("The strings are equal\n"); }
    else if (compare > 0) {
		printf("String 1 is bigger\n"); }
    else {
		printf("String2 is bigger\n");
	}


	compare = strncmp(string1, string2,number);

	if (compare == 0) {
		printf("The first %d character of both strings are equal\n",number); }
    else if (compare > 0) {
		printf("String 1 is bigger when comparing %d characters\n",number); }
    else {
		printf("String2 is bigger when comparing %d characters\n",number);
	}


	strcat(string1, string2);

	printf("String 1 now is %s and string 2 remain %s\n", string1, string2);

	strncat(string1, string2,number);

	printf("String 1 now is %s and string 2 remain %s\n", string1, string2);

	printf("The length of string1 is: %d\n", strlen(string1));

	printf("The length of string2 is: %d\n", strlen(string2));


	strcpy(string1, string2);

	printf("String 1 now is %s and string 2 remain %s\n", string1, string2);

	strncpy(string1, "BBBBBBB",2);

	string1[2] = '\0';

	printf("String 1 now is %s and string 2 remain %s\n", string1, string2);


	for (i = 0;i < 7;i++) {
		printf("Please enter the name of day %d\n", i + 1);
		scanf("%s", namesofweek[i]);
	}


	for (i = 0;i < 7;i++) {
		printf("The name of day %d is %s\n", i + 1,namesofweek[i]);
	}

	for (i = 0;i < 12;i++) {
		printf("Please enter the temperature for %s\n", Months[i]);
	}

}
