#include "pedido.hpp"


Pedido::~Pedido() {
  // TODO: Implemente este metodo.
  /**
   * Aqui voce deve deletar os ponteiros contidos na lista m_produtos
   */
    for(auto &produto: m_produtos)
        delete produto;
}

void Pedido::setEndereco(const std::string& endereco) {
  // TODO: Implemente este metodo.
    m_endereco = endereco;
}

float Pedido::calculaTotal() const {
  // TODO: Implemente este metodo.
    float soma = 0;

    for(auto &produto: m_produtos)
        soma += produto->getValor() * produto->getQtd();

  return soma;
}

void Pedido::adicionaProduto(Produto* p) {
  // TODO: Implemente este metodo.
    m_produtos.push_back(p); 
}

std::string Pedido::resumo() const {
  // TODO: Implemente este metodo.
  /**
   * Aqui voce deve percorrer a lista de produtos para criar um resumo completo
   * do pedido. A cada iteracao, utilize o metodo descricao de cada produto para
   * montar o resumo do pedido. Por fim, adicione o endereco de entrega.
   *
   */
    std::string str = "";
    for(auto &produto: m_produtos)
        str += produto->descricao() + "\n";
    
    str += "Endereco: " + m_endereco + "\n";

    return str;
}
