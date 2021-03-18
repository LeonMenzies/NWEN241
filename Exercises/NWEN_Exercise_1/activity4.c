#include <stdio.h>

int main(void){
    float ctemp;
    float ftemp;

    printf("Enter temperature: ");
    scanf("%f", &ctemp);

    ftemp = (ctemp * 9/5) + 32;

    printf("%.3f\n", ftemp);
}