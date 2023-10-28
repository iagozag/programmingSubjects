#include "../include/verifying_coloring.h"

bool verify_coloring(ListaAdjacencia* list){
    for(int i = 0; i < list->getTam(); i++){
        NodeType* cur = list->getArestas(i).at(0);
        for(int j = 0; j < list->getArestas(i).getLength(); j++){
            
        }
    }  

    return true;
}
