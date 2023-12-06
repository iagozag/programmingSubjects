#include <stdio.h>

int eh_perfeito(int n){
    int soma = 0;
    for(int i = 1; i <= n/2; i++){
        if(n % i == 0) soma += i;
    }
    return(soma == n);
}

int eh_palindromo(char* s, int n){
    int j = n - 1;
    for(int i = 0; i < n; i++){
        if(s[i] != s[j]) return(0);
        j--;
        if(i==j) break;
    }
    return(1);
}



//int main(){
//    int a, b = 1; scanf("%d", &a);
//    int total;
//    do{
//        total = a * b;
//        a = total;
//        scanf("%d", &b);
//    } while(b != 0);
//    printf("total: %d", total);
//    return(0);
//}

int main(){
    char s[100];
    int n;

    FILE* f = fopen("texto.txt", "r+t");
    if(f == NULL){
        printf("ERRO ARQUIVO");
        return(1);
    }
    fscanf(f, "%s", s);
    printf("%s eh palindromo: %d", s, eh_palindromo(s, strlen(s)));
    return(0);
}
