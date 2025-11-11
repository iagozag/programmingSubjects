#include "pizza.hpp"

std::string Pizza::descricao() const {
  // TODO: Implemente este metodo.
  /*
   * Note que aqui voce deve retornar uma descricao detalhada da pizza.
   *
   * Exemplos:
   * 2X Pizza Calabresa, 4 pedacos e borda recheada.
   * 2X Pizza Calabresa, 4 pedacos sem borda recheada.
   */
    std::string str = std::to_string(m_qtd);
    str += "X Pizza " + _sabor + ", ";
    str += std::to_string(_pedacos) + " pedacos e ";
    (_borda_recheada) ? str += "borda recheada." : str += "sem borda recheada.";

  return str;
}

Pizza::Pizza(
    const std::string& sabor,
    int pedacos,
    bool borda_recheada,
    int qtd,
    float valor_unitario
    ): _sabor(sabor),
    _pedacos(pedacos),
    _borda_recheada(borda_recheada) {
    m_qtd = qtd;
    m_valor_unitario = valor_unitario;
}
