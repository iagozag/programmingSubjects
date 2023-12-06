#include <stdio.h>

int main(){
    int mat[3][3] = {
    {5, -8, 10},
    {1, 2, 15},
    {25, 10, 7}
    };
    int soma = 0;

    for(int i = 0; i < 3; i++){
        soma += mat[i][2 - i];
    }

    printf("%d", soma);
    return(0);
}
