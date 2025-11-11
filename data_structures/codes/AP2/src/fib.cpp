#include <bits/stdc++.h>
#include "../include/fib.h"

int retornaFibonacciIterativo(int n){
    int first = 0, second = 1, third;

    if(n == 0) return first;
    for(int i = 2; i <= n; i++) {
        third = first + second;
        first = second;
        second = third;
    }

    return second;
}

int retornaFibonacciRecursivo(int n){
    if(n == 1 || n == 2) return 1;
    
    // for(int i = 0; i < 100; i++) sin(n);
    return retornaFibonacciRecursivo(n-1) + retornaFibonacciRecursivo(n-2);
}
