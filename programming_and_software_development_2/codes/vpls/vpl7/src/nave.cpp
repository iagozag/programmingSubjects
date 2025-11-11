#include "../include/nave.h"
using namespace std;

Nave::Nave(){}

Nave::Nave(Ponto2D posicao, double forca){
    _posicao = posicao;
    _forca = forca;
}

void Nave::mover(double dx, double dy){
    _posicao = Ponto2D(_posicao.get_x() + dx, _posicao.get_y() + dy);
}

double Nave::calcular_distancia(Nave nave){
    return(_posicao.calcular_distancia(nave._posicao));
}

int Nave::determinar_indice_nave_mais_proxima(Nave naves[], int n){
    int min_distance = calcular_distancia(naves[0]._posicao);
    if(min_distance == 0) min_distance = 1000000000;

    int min_index = 0;
    for(int i = 1; i < n; i++){
        if(calcular_distancia(naves[i]._posicao) == 0) continue;

        if(calcular_distancia(naves[i]._posicao) < min_distance){
            min_distance = calcular_distancia(naves[i]._posicao);
            min_index = i;
        }
    }

    return(min_index);
}

void Nave::atacar(Nave naves[], int n){
    int index = determinar_indice_nave_mais_proxima(naves, n);
    double dano = (100 * _forca) / calcular_distancia(naves[index]);

    if(dano > 30) naves[index]._energia -= 30;
    else naves[index]._energia -= dano;

    if(naves[index]._energia <= 50) cout << "Energia baixa!" << "\n";
}

void Nave::imprimir_status(){
    cout << _posicao.get_x() << " " << _posicao.get_y() << " " << _energia << "\n";
}
