#include <stdio.h>

int dig(int num, int d, int soma){
    if(num % 10 == d) soma ++;
    if(num / 10 == 0) return soma;
    return(dig(num / 10, d, soma));
}

int main(){
    int n, d; scanf("%d %d", &n, &d);
    printf("o numero %d ocorre %d vezes", d, dig(n, d, 0));
}
