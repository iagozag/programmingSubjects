#include <stdio.h>

int main(){
    int age, i = 0;
    float height, soma = 0;

    do{
        scanf("%d %f", &age, &height);
        if(age >= 40 && age <= 50){
            soma += height;
            i++;
        }
    } while(age > 0 && height > 0);

    printf("%.2f", soma / i);
}
