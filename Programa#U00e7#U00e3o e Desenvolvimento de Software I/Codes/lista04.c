#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int fat(int n){
	if(n == 0) return 1;
	return(n * fat(n - 1));
}

int mdc(int a, int b){
	if(b == 0) return a;
	return(mdc(b, a % b));
}

int mdc3(int a, int b, int c){
    if(c == 0) return mdc(a, b);
    return mdc3(c, mdc(a, b), mdc(a, b) % c);
}

int fib(int n){
	if(n <= 1) return n;
	return(fib(n - 1) + fib(n - 2));
}

int primo(int x, int n){
	if(n == 1) return 1;
	if(x % n == 0) return 0;
	return(primo(x, n - 1));
}

void decrescente(int x){
    printf("%d ", x);
    if(x == 1){
        return;
    }
    return decrescente(x - 1);
}

int res(int a, int b){
	if(a - b < 0) return a;
	return(res(a - b, b));
}

int form(int n){
	if(n <= 1) return n;
	return((n * n) + form(n - 1));
}

int mmc(int a, int b){
    if(mdc(a, b) == 1) return a * b;
    if(a > b) return(mmc(a, b / mdc(a, b)));
    if(b > a) return(mmc(a / mdc(a, b), b));
}

int divisao(int a, int b){
    if(b > a) return 0;
	if(a - b < 0) return 0;
	return(1 + divisao(a - b, b));
}

float raiz(float x, float chute){
	if(chute * chute < x + 0.001 && chute * chute > x - 0.001) return(chute);
	if(chute * chute > x) return(raiz(x, chute * 0.5));
	if(chute * chute < x) return(raiz(x, chute * 1.5));
}

int dig(int n){
    if(n == 0) return n;
    return(n % 10 + dig(n / 10));
}

int expo(int k, int n){
    if(n == 1) return k;
    return(expo(k, n - 1) * k);
}

void crescente(int x){
    if(x > 1) crescente(x - 1);
    printf("%d ", x);
}

int main(){
	int a, b, c, n, x, k;
	float d;
	printf("a  b  c  d  n  x  k\n");
	scanf("%d %d %d %f %d %d %d", &a, &b, &c, &d, &n, &x, &k);

	printf("fatorial de %d: %d\n", n, fat(n));
	printf("fibonacci de %d: %d\n", n, fib(n));
	printf("mdc entre %d e %d eh: %d\n", a, b, mdc(a, b));
	printf("mdc3 entre %d, %d e %d eh: %d\n", a, b, c, mdc3(a, b, c));
	printf("%d eh primo: %d\n", x, primo(x, sqrt(x)));
	printf("Decrescentes de %d: ", x);
    decrescente(x);
    if(a > b){
        printf("\nO resto da divisao de %d e %d eh: %d", a, b, res(a, b));
    } else{
        printf("\nO resto da divisao de %d e %d eh: %d", a, b, 0);
    }
    printf("\nO form de %d eh: %d", n, form(n));
    printf("\nO mmc de %d e %d eh: %d", a, b, mmc(a, b));
    printf("\nA divisao de %d e %d eh: %d", a, b, divisao(a, b));
	printf("\na raiz aproximada de %f eh: %f\n", d, raiz(d, d/2));
    printf("a soma dos digitos de %d eh: %d\n", n, dig(n));
    printf("%d elevado a %d eh: %d\n", k, n, expo(k, n));
    printf("Crescentes ate %d: ", x);
    crescente(x);
	return 0;
}

