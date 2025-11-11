#include<stdio.h>
#include <time.h>
#include <stdlib.h>


int rolaDados(){
    int r, soma = 0;
    for(int i = 0; i < 3; i++){
        r = rand() % 7;
        soma += r;
    }
    return soma;
}

struct Guerreiro{
    int ataque;
    int defesa;
    int pontos_vida;
    int id_jogador;
    void atribuir_id(int id);
    void atribuir(int ata, int def, int pv, int id);
    int ataca(Guerreiro& g1, Guerreiro& g2);

};

void Guerreiro::atribuir_id(int id){
    id_jogador = id;
}

void Guerreiro::atribuir(int ata, int def, int pv, int id){
    ataque = ata;
    defesa = def;
    pontos_vida = pv;
    id_jogador = id;
}

void ataca(Guerreiro& g1, Guerreiro& g2){
    int golpe = g1.ataque + rolaDados();
    int escudo = g2.defesa + rolaDados();
    int dano = golpe - escudo;
    if(dano > 0) g2.pontos_vida -= dano;
}

void criaGuerreiro(Guerreiro& g){
    g.atribuir(rolaDados(), rolaDados(), rolaDados(), g.id_jogador);
}

int main(){
    srand(time(NULL));

    Guerreiro iago, carol;
    iago.atribuir_id(1);
    carol.atribuir_id(2);
    criaGuerreiro(iago);
    criaGuerreiro(carol);

    printf("iago - ata: %d, def: %d, pv: %d, id: %d\n", iago.ataque, iago.defesa, iago.pontos_vida, iago.id_jogador);
    printf("carol - ata: %d, def: %d, pv: %d, id: %d\n\n", carol.ataque, carol.defesa, carol.pontos_vida, carol.id_jogador);

    int turn = 1;
    while(iago.pontos_vida > 0 && carol.pontos_vida > 0){
        if(turn == 1){
            ataca(iago, carol);
            turn = 2;
        }
        else{
            ataca(carol, iago);
            turn = 1;
        }
        printf("iago - ata: %d, def: %d, pv: %d\n", iago.ataque, iago.defesa, iago.pontos_vida, iago.id_jogador);
        printf("carol - ata: %d, def: %d, pv: %d\n\n", carol.ataque, carol.defesa, carol.pontos_vida, carol.id_jogador);
    }

    if(iago.pontos_vida <= 0){
        iago.pontos_vida = 0;
        printf("Vencedor: Carol\npontos de vida Iago: %d | pontos de vida Carol: %d", iago.pontos_vida, carol.pontos_vida);
    }
    else if(carol.pontos_vida <= 0){
        carol.pontos_vida = 0;
        printf("Vencedor: Iago\npontos de vida Iago: %d | pontos de vida Carol: %d", iago.pontos_vida, carol.pontos_vida);
    }
    return(0);
}
