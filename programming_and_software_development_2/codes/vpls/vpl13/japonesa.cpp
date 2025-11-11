#include "japonesa.hpp"

std::string Japonesa::descricao() const {
  // TODO: Implemente este metodo.
  /*
   * Note que aqui voce deve retornar uma descricao detalhada da comida
   * japonesa.
   *
   * Exemplos:
   * 1X Comida japonesa - Combo 1, 4 sushis, 5 temakis e 6 hots.
   * 1X Comida japonesa - Combo 2, 5 sushis, 6 temakis e 8 hots.
   */
   
    std::string str = std::to_string(m_qtd);
    str += "X Comida japonesa - ";
    str += _combinado + ", ";
    str += std::to_string(_sushis) + " sushis, ";
    str += std::to_string(_temakis) + " temakis e ";
    str += std::to_string(_hots) + " hots.";

  return str;
}

Japonesa::Japonesa(
    const std::string& combinado,
    int sushis,
    int temakis,
    int hots,
    int qtd,
    float valor_unitario
    ): _combinado(combinado),
       _sushis(sushis),
       _temakis(temakis),
       _hots(hots) {
    m_qtd = qtd;
    m_valor_unitario = valor_unitario;
}
