#include <exception>
#include <iostream>

#include "../include/sistema.h"

int main() {
    Sistema sistema_uber = Sistema();

    try
    {
        sistema_uber.adicionar_carro("branco", 0);
        sistema_uber.adicionar_carro("verde", 2);
        sistema_uber.adicionar_carro("verde", 1);
        sistema_uber.adicionar_carro("vermelho", 10);

        sistema_uber.adicionar_carro("verde", 1);
    }
    catch (id_ja_existe_e &e)
    {
        std::cout << "Id do carro já existe" << std::endl;
    }

    Cliente *flavio = sistema_uber.cadastra_cliente("flavio@dcc");
    Cliente *ana = sistema_uber.cadastra_cliente("ana@dcc");
    Cliente *pedro = sistema_uber.cadastra_cliente("pedro@dcc");

    try
    {
        sistema_uber.cadastra_cliente("flavio@dcc");
    }
    catch (cliente_ja_existe_e &e)
    {
        std::cout << "O cliente já existe!" << std::endl;
    }

    try
    {
        flavio->adicionar_saldo(-2);
    }
    catch (impossivel_adicionar_saldo_negativo_e &e)
    {
        std::cout << "Não podemos adicionar saldo negativo" << std::endl;
    }

    flavio->adicionar_saldo(50);
    ana->adicionar_saldo(20);

    try
    {
        ana->remover_saldo(50);
    }
    catch (saldo_insuficiente_para_remocao_e &e)
    {
        std::cout << "Não posso remover saldo de valor 50 de ana" << std::endl;
    }

    try
    {
        Carro *cf = sistema_uber.busca_uber("flavio@dcc");
        std::cout << "Carro de placa " << cf->get_id();
        std::cout << " está ocupado? " << cf->ocupado() << std::endl;
    }
    catch (zero_carros_disponiveis_e &e)
    {
        std::cout << "Zero carros disponíveis!" << std::endl;
    }
    catch (cliente_nao_existe_e &e)
    {
        std::cout << "Cliente não existe!" << std::endl; 
    }
    catch (sem_saldo_e &e)
    {
        std::cout << "Sem saldo!" << std::endl;
    }
   
    try
    {
        Carro *cf = sistema_uber.busca_uber("ana@dcc");
        std::cout << "Carro de placa " << cf->get_id();
        std::cout << " está ocupado? " << cf->ocupado() << std::endl;
    }
    catch (zero_carros_disponiveis_e &e)
    {
        std::cout << "Zero carros disponíveis!" << std::endl;
    }
    catch (cliente_nao_existe_e &e)
    {
        std::cout << "Cliente não existe!" << std::endl; 
    }
    catch (sem_saldo_e &e)
    {
        std::cout << "Sem saldo!" << std::endl;
    }

    try
    {
        sistema_uber.busca_uber("pedro@dcc");
    }
    catch (zero_carros_disponiveis_e &e)
    {
        std::cout << "Zero carros disponíveis!" << std::endl;
    }
    catch (cliente_nao_existe_e &e)
    {
        std::cout << "Cliente não existe!" << std::endl; 
    }
    catch (sem_saldo_e &e)
    {
        std::cout << "Não posso alocar um carro para pedro!" << std::endl;
    }

    return(0);
}