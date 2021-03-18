#include <stdio.h>

int main(void){
    printf("Enter a string: ");
    char userInput[100];
    scanf("%[^\n]s", &userInput);

    printf("%s\n", userInput);

    return 0;
}