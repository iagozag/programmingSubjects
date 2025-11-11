#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int fat(int n){
    for(int i = n - 1; i > 0; i--){
        n *= i;
    }
	return(n);
}

int mdc(int a, int b){
    int aux;

    while(b > 0){
        aux = b;
        b = a % b;
        a = aux;
        if(b == 0) return a;
    }
}

int mdc3(int a, int b, int c){
    return(mdc(mdc(a, b), c));
}

int fib(int n){
    int primeiro = 0, segundo = 1, prox;

    for(int i = 0; i < n; i++){
        if(i <= 1) prox = i;
        else{
            prox = primeiro + segundo;
            primeiro = segundo;
            segundo = prox;
        }
    }
	return(prox);
}

int primo(int x){
    for(int i = 2; i <= sqrt(x); i++){
	if(x % i == 0) return 0;
    }
    return 1;
}

void decrescente(int x){
    for(int i = x; i > 0; i--){
        printf("%d ", i);
    }
}

int res(int a, int b){
    while(a - b >= 0){
        a -= b;
    }
    return a;
}

int form(int n){
    int soma;
    for(int i = 1; i <= n; i++){
        soma += i*i;
    }
    return soma;
}

int mmc(int a, int b){
    do{
        return((a * b) / mdc(a, b));
    } while(mdc(a, b) != 1);
    return a * b;
}

int divisao(int a, int b){
    int qnt;
    while(a - b >= 0){
        a -= b;
        qnt++;
    }
    return qnt;
}

float raiz(float x, float chute){
    while((chute * chute > x + 0.001) || (chute * chute < x - 0.001)){
        if(chute * chute > x) chute *= 0.5;
        if(chute * chute < x) chute *= 1.5;
    }
    return chute;
}

int dig(int n){
    int soma;
    while(n != 0){
        soma += n % 10;
        n /= 10;
    }
    return soma;
}

int expo(int k, int n){
    int resultado = 1;
    for(int i = 0; i < n; i++){
        resultado *= k;
    }
    return resultado;
}

void crescente(int x){
    for(int i = 1; i <= x; i++){
         printf("%d ", i);
    }
}

int main(){
	int a, b, c, n, x, k;
	float d;
	printf("a  b  c  d  n  x  k\n");
	scanf("%d %d %d %f %d %d %d", &a, &b, &c, &d, &n, &x, &k);

	printf("fatorial de %d: %d\n", n, fat(n));
	printf("mdc entre %d e %d eh: %d\n", a, b, mdc(a, b));
	printf("mdc3 entre %d, %d e %d eh: %d\n", a, b, c, mdc3(a, b, c));
	printf("fibonacci de %d: %d\n", n, fib(n));
	printf("%d eh primo: %d\n", x, primo(x));
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

