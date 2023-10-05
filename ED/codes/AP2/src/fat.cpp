#include <bits/stdc++.h>
#include "../include/fat.h"

unsigned long long retornaFatorialIterativo(int n){
    unsigned long long ans = 1;
    for(int i = 2; i <= n; i++) ans *= i;
    
    return ans;
}

unsigned long long retornaFatorialRecursivo(int n){
    if(n == 1) return 1;
    
    // for(int i = 0; i < 100; i++) sin(n);
    return n*retornaFatorialRecursivo(n-1);
}
