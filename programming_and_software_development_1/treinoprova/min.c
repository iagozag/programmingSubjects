#include<stdio.h>

int minimum(int* v, int n, int m){
    if(n < 1) return m;
    if(v[n] < m) m = v[n];
    return(minimum(v, n - 1, m));
}

int main(){
    int n; scanf("%d", &n);
    int v[n];
    for(int i = 0; i < n; i++){
        scanf("%d", &v[i]);
    }

    printf("min: %d\n", minimum(v, n - 1, v[0]));
    return(0);
}
