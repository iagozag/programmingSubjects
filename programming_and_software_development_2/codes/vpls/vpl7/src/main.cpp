#include <iostream>
#include <iomanip>

#include "../include/nave.h"

using namespace std;

int main() {
  
    // Lendo quantidade de naves na batalha
    int num_naves;
    cin >> num_naves;

    // Criando o vetor de naves
    Nave naves[num_naves]; 

    // Preenchendo o vetor com os dados de entrada
    double x, y, forca;
    for (int i = 0; i < num_naves; i++) {
        cin >> x >> y >> forca;
        naves[i] = Nave(Ponto2D(x, y), forca);
    }

    // Definindo o formato da saida
    cout << fixed << showpoint; 
    cout << setprecision(2);

    // Executando as jogadas
    int idx;
    char data;
    while (cin >> data) {
        switch (data) {
            
            // Imprimindo status de todas as naves
            case 's':                 
                for (int i = 0; i < num_naves; i++)
                    naves[i].imprimir_status();

                break;

            // Calculo da distancia entre todas as naves
            case 'd': 
                for (int i = 0; i < num_naves; i++)
                    for (int j = 0; j < num_naves; j++)
                        cout << naves[i].calcular_distancia(naves[j]) << endl;
                
                break;

            // Realizar ataque
            case 'a':                  
                cin >> idx; // Index da nave que fará o ataque

                naves[idx].atacar(naves, num_naves);
                
                break;   

            // Mover
            case 'm':                  
                cin >> idx; // Index da nave que vai mover

                double dx, dy;
                cin >> dx >> dy; // Deslocamento

                naves[idx].mover(dx, dy);
                
                break;     

            // Verificar nave mais proxima
            case 'p':                  
                cin >> idx; // Index da nave que vamos usar de base

                int indice_nave = naves[idx].determinar_indice_nave_mais_proxima(naves, num_naves);

                naves[indice_nave].imprimir_status();
                
                break;                                              
        }
    }
    
    return 0;
}
