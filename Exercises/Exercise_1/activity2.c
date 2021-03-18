#include <stdio.h>

int main(void){
    printf("Enter a string without whitespaces: ");
    char userInput[100];
    scanf("%s", &userInput);
    printf("%s", userInput);

    return 0;
}