#!/usr/bin/env python3
import sys
import grpc
import kv_pb2  # Importa as classes de Mensagens (Request, Reply)
import kv_pb2_grpc  # Importa as classes de Stub (cliente) e Servicer (servidor)


if __name__ == "__main__":
    # O cliente recebe um único argumento: o locator do servidor central
    locator = sys.argv[1]
    
    # Cria um canal de comunicação gRPC inseguro (sem SSL/TLS)
    channel = grpc.insecure_channel(locator)
    
    # Cria um "Stub" (cliente) para o serviço 'CentralService'
    stub = kv_pb2_grpc.CentralServiceStub(channel)

    # Lê comandos da entrada, linha por linha
    for raw in sys.stdin:
        line = raw.rstrip('\n')  # Remove a quebra de linha

        # Ignora linhas em branco
        if not line:
            continue

        # --- Comando 'T' (Terminate) ---
        if line == 'T':
            # Chama o RPC 'Terminate' no servidor
            resp = stub.Terminate(kv_pb2.TerminateRequest())
            print(resp.total)  # Imprime o total de chaves retornado
            break  # Encerra o cliente

        # --- Comando 'P' (Pairing) ---
        elif line.startswith('P '):
            try:
                # Extrai o locator (ex: "P ganges:6666" -> "ganges:6666")
                _, loc = line.split(' ', 1)
                
                # Chama o RPC 'Pairing'
                resp = stub.Pairing(kv_pb2.PairingRequest(locator=loc.strip()))
                print(resp.result)
            except Exception:
                # Ignora comandos mal formados ou falhas no RPC
                continue

        # --- Comando 'B' (Search) ---
        elif line.startswith('B '):
            try:
                # Extrai a chave (ex: "B 10" -> 10)
                _, chs = line.split(' ', 1)
                ch = int(chs.strip())
                
                # 1. Primeira Chamada (para o Servidor Central)
                # Chama o RPC 'Search' para descobrir *onde* a chave está
                resp = stub.Search(kv_pb2.SearchRequest(key=ch, except_=""))
                
                # Se o locator retornado não for vazio, a chave foi encontrada
                if resp.locator:
                    # Imprime a primeira parte da saída (ex: "xingu:5555=")
                    print(f"{resp.locator}=", end="")
                    
                    # 2. Segunda Chamada (para o Servidor de Pares)
                    # Implementa o "estilo Napster": agora conecta-se diretamente
                    # ao servidor de pares que o central indicou.
                    try:
                        # Cria um novo canal e novo stub para o 'PairService'
                        pch = grpc.insecure_channel(resp.locator)
                        pstub = kv_pb2_grpc.PairServiceStub(pch)

                        # Chama o RPC 'Query' no servidor de pares
                        qresp = pstub.Query(kv_pb2.QueryRequest(key=ch), timeout=5)
                        
                        # Imprime o valor final (ex: "DEZ"), completando a linha
                        print(qresp.value)
                    except Exception:
                        # Se a segunda chamada (Query) falhar, imprime linha em branco
                        # para completar a saída (ex: "xingu:5555=\n")
                        print("")
            except Exception:
                # Se a primeira chamada (Search) falhar, ignora e continua o loop
                continue

        # Ignora qualquer outra linha
        else:
            continue