#include <stdio.h>
int mult(int n1, int n2){
    if(n1 < 0 && n2 < 0){
        if(n2 == -1) return -(n1);
        return (-(n1) + mult(n1, n2 + 1));
    } else{
        if(n2 == 1) return n1;
        return (n1 + mult(n1, n2 - 1));
    }
}

int main(){
    int a, b;
    while(scanf("%d %d", &a, &b)){
        printf("%d vezes %d eh: %d\n", a, b, mult(a, b));
    }
}
