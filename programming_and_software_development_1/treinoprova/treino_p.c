#include<stdio.h>
#include<math.h>

struct Ponto{
    float x, y;
    void atribuir(float a, float b);
    float distancia();
};

struct Restaurante{
    Ponto p;
    float preco;
    char nome[100];
    void atribuir(float a);
    void atribuir_nome(char s[100]);
    void imprime();
};

//PONTO
float Ponto::distancia(){
    return(sqrt((x * x) + (y * y)));
}

void Ponto::atribuir(float a, float b){
    x = a;
    y = b;
}

//RESTAURANTE

void Restaurante::atribuir(float a){
    preco = a;
}

void Restaurante::atribuir_nome(char s[100]){
    for(int i = 0; i < 100; i++) nome[i] = s[i];
}

void Restaurante::imprime(){
    printf("- %s\n", nome);
}

//FUNCAO IMPRIME RESPOSTA
void imprime_perto(Restaurante rests[], int range, int qnt){
    for(int i = 0; i < qnt; i++)
    if(rests[i].p.distancia() <= range) rests[i].imprime();
}

void imprime_perto_barato(Restaurante rests[], int range, float price, int qnt){
    for(int i = 0; i < qnt; i++)
    if(rests[i].p.distancia() <= range && rests[i].preco <= price) rests[i].imprime();
}

int main(){
    Restaurante rmap[10];
    int x, y;
    float preco;
    char nome[100];

    //ABRE ARQUIVO
    FILE* f = fopen("restaurants.txt", "r+t");
    if(f == NULL){
        printf("ERRO AO ABRIR ARQUIVO");
        return(1);
    }

    int i = 0, m;
    float max_price;
    printf("Distancia maxima: ");
    scanf("%d", &m);
    printf("Preco maximo: ");
    scanf("%f", &max_price);

    while(fscanf(f, "%d %d", &x, &y) != EOF){
        fscanf(f, "%f", &preco);
        fscanf(f, "%s", nome);
        rmap[i].p.atribuir(x, y);
        rmap[i].atribuir(preco);
        rmap[i].atribuir_nome(nome);
        i++;
    }

    printf("Restaurantes por perto:\n");
    imprime_perto(rmap, m, i);
    printf("\nRestaurantes por perto e baratos:\n");
    imprime_perto_barato(rmap, m, max_price, i);

    fclose(f);
    return(0);
}
