#include <stdio.h>

int is_prime(int n){
    for(int i = 2; i * i < n; i++){
        if(n % i == 0) return(0);
    }
    return(1);
}

int main(){
    int n, p; scanf("%d", &n);
    for(int i = 0; i < n; i++){
        scanf("%d", &p);
        if(is_prime(p) == 1) printf("Prime\n");
        else printf("Not Prime\n");
    }

    return(0);
}
