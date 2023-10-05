#include "venda.hpp"

#include <cmath>
#include <iomanip>
#include <iostream>
#include <algorithm>
#include <cctype>

void Venda::adicionaCelular(const Celular& celular) {
    m_celulares.push_back(celular); 
}

void Venda::ordena() {
  // TODO: Implemente este metodo
  // Preste atencao no exemplo que a descricao utilizada na ordenacao considera
  // a fabricante antes do modelo do celular
    m_celulares.sort();
}

void Venda::recarregaEstoque(int cod, int qtd) {
    for(auto &cel: m_celulares){
        if(cel.get_codigo() == cod){
            cel._qtd += qtd;
        } 
    }
}

void Venda::efetuaVenda(int cod, int qtd) {
  // TODO: Implemente este metodo
  /**
   * Observe na descricao do enunciado que nao e permita a venda de um modelo
   * cuja quantidade seja maior que a quantidade atual em estoque.
   * Ex: Se existirem apenas 5 celulares Motorola Moto G50 em estoque, vendas a
   * partir de 6 unidades devem ser ignoradas.
   */
    for(auto &cel: m_celulares){
        if(cel.get_codigo() == cod){
            if(cel._qtd < qtd) break;

            cel._qtd -= qtd;
            break;
        } 
    }
}

void Venda::aplicaDesconto(const std::string& fabricante, float desconto) {
  // TODO: Implemente este metodo
    for(auto &cel: m_celulares){
        if(cel._fabricante == fabricante){
            cel._valor -= cel._valor * (desconto/100);
        } 
    }
}

void Venda::removeModelo(int cod) {
  // TODO: Implemente este metodo
    std::list<Celular>::iterator itr = m_celulares.begin();
    std::list<Celular> temporary;
    while(itr != m_celulares.end()) {
        if(itr->get_codigo() != cod){
            temporary.push_back(*itr);
        }
        itr++;
    }
    m_celulares = temporary;
}

void Venda::imprimeEstoque() const {
  // TODO: Implemente este metodo.
  /**
   * Aqui voce tera que imprimir a lista de celulares em estoque com as
   * restricoes descritas no enunciado do problema. Notem no exemplo que a
   * primeira letra da cor do celular fica maiuscula. Outra coisa, se houver
   * apenas um item em estoque de determinado modelo de celular, voce tera que
   * imprimir '1 restante' e nao '1 restantes'. Por ultimo, apenas modelos de
   * celulares com pelo menos um item em estoque deverao ser exibidos.
   */
    for(auto &cel: m_celulares){
        if(cel._qtd == 0) continue;
       
        std::string cor = cel.get_cor();
        cor[1] -= 32;

        std::cout << cel.get_fabricante() << " " << cel.get_modelo() << ", "
            << cel.get_armazenamento() << "GB, " << cel.get_memoria() << "GB RAm, "
            << std::fixed << std::setprecision(0) << cel.get_peso()*1000 << " gramas, "
            << cor << ", ";
        
        if(cel._qtd == 1) std::cout << cel.get_qtd() << " restante, ";
        else std::cout << cel.get_qtd() << " restantes, "; 
        
        std::cout << "R$ " << std::fixed << std::setprecision(2) << cel.get_valor();

        std::cout << std::endl;
    }
}
