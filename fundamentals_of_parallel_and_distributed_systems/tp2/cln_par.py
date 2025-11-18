#!/usr/bin/env python3
import sys
import grpc
import kv_pb2  # Importa as classes de Mensagens (Request, Reply)
import kv_pb2_grpc  # Importa as classes de Stub (cliente)

if __name__ == "__main__":
    # O cliente recebe um único argumento: o locator do servidor de pares
    locator = sys.argv[1]
    
    # Cria um canal de comunicação gRPC inseguro (sem SSL/TLS)
    channel = grpc.insecure_channel(locator)
    
    # Cria um "Stub" (cliente) para o serviço 'PairService'
    stub = kv_pb2_grpc.PairServiceStub(channel)

    # Lê comandos da entrada padrão, linha por linha
    for raw in sys.stdin:
        line = raw.rstrip("\n")  # Remove a quebra de linha

        # Ignora linhas em branco
        if not line:
            continue

        # --- Comando 'I' (Insert) ---
        if line.startswith('I '):
            try:
                # Parseia a linha: "I 10 valor"
                _prefix, rest = line.split(' ', 1)
                ch_str, val = rest.split(' ', 1)  # 'val' pega todo o resto da linha
                ch = int(ch_str)  # Converte a chave para inteiro

                # Chama o RPC 'Insert' no servidor
                resp = stub.Insert(kv_pb2.InsertRequest(key=ch, value=val))
                print(resp.result)  # Imprime 0 (inserido) ou 1 (atualizado)
            except Exception:
                # Ignora comandos mal formados ou falhas no RPC
                continue

        # --- Comando 'C' (Query/Consult) ---
        elif line.startswith('C '):
            try:
                # Parseia a linha: "C 10"
                _prefix, chs = line.split(' ', 1)
                ch = int(chs.strip())  # Converte a chave para inteiro

                # Chama o RPC 'Query' no servidor
                resp = stub.Query(kv_pb2.QueryRequest(key=ch))
                print(resp.value)  # Imprime o valor (ou "" se não encontrado)
            except Exception:
                # Ignora comandos mal formados ou falhas no RPC
                continue

        # --- Comando 'A' (Activate) ---
        elif line == 'A':
            # Chama o RPC 'Activate' no servidor
            resp = stub.Activate(kv_pb2.ActivateRequest())
            print(resp.result)  # Imprime o resultado (0 na Parte 1, N na Parte 2)

        # --- Comando 'T' (Terminate) ---
        elif line == 'T':
            # Chama o RPC 'Terminate' no servidor
            resp = stub.Terminate(kv_pb2.TerminateRequest())
            print(resp.total)  # Imprime o total de chaves
            break  # Encerra o cliente

        # Ignora qualquer outra linha
        else:
            continue