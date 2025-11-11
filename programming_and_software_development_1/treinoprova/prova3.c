#include<stdio.h>

struct Individuo{
    int id;
    int n;
    int pontos[1000];
    void atribuir(int id_i);
    void atribuir_pontos(int p, int i);
    int soma();
};

void Individuo::atribuir(int id_i){
    id = id_i;
}

void Individuo::atribuir_pontos(int p, int i){
    pontos[i] = p;
}

int Individuo::soma(){
    int sum = 0;
    for(int j = 0; j < n; j++){
        sum += pontos[j];
    }
    return sum;
}

int main(){
    int ponto;
    Individuo k;
    scanf("%d", &k.n);
    k.atribuir(12345);
    for(int i = 0; i < k.n; i++){
        scanf("%d", &ponto);
        k.atribuir_pontos(ponto, i);
    }
    printf("Individuo ID: %d\n", k.id);
    printf("A soma dos pontos eh: %d", k.soma());
}
