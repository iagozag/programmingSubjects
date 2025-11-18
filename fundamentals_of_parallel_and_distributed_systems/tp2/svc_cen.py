#!/usr/bin/env python3
import sys
import threading
import socket
from concurrent import futures

import grpc
import kv_pb2
import kv_pb2_grpc

# Define a classe do "Servidor Central"
# Esta classe implementa os serviços 'CentralService' definidos no kv.proto
class CentralServicer(kv_pb2_grpc.CentralServiceServicer):
    
    # Construtor do servidor
    def __init__(self, stop_event, port, super_mode=False):
        self.lock = threading.Lock()  # Lock para proteger o diretório e a lista de pares
        self.directory = {}  # Dicionário [chave:int] -> [locator:str]
        
        # 'super_peers' é a lista de outros super-pares (Parte 3)
        # Se não estiver em super_mode (Parte 2), a lista é None.
        self.super_peers = [] if super_mode else None
        
        self.stop_event = stop_event  # Evento para sinalizar o término
        self.port = port
        
        # Se estiver no modo super-par, armazena o próprio locator
        # Isso evita loop na busca da Parte 3
        self.locator = f"{socket.getfqdn()}:{self.port}" if super_mode else ""

    # Implementação do RPC 'Register'
    # Usado pelo 'svc_par' para anunciar suas chaves
    def Register(self, request, context):
        processed = 0
        with self.lock:  # Adquire o lock para modificar o 'directory'
            for k in request.keys:
                # Associa cada chave ao locator do servidor de pares que a registrou
                # Sobrescreve se a chave já existia
                self.directory[int(k)] = request.locator
                processed += 1

        return kv_pb2.RegisterReply(processed=processed)

    # Implementação do RPC 'Search'
    def Search(self, request, context):
        key = int(request.key)
        
        # 'except_' é usado na Parte 3 para evitar loops
        except_locator = request.except_
        
        # --- Parte 2: Busca Local ---
        with self.lock:
            # Procura a chave no diretório local
            loc = self.directory.get(key, "")

        if loc:
            # Chave encontrada localmente, retorna o locator do 'svc_par'
            return kv_pb2.SearchReply(locator=loc)
        
        # --- Parte 3: Busca Recursiva ---
        
        # Se a chave não foi encontrada e não estamos em modo super-par, termina a busca.
        if self.super_peers is None:
            return kv_pb2.SearchReply(locator="")
        
        # Se estamos em modo super-par, encaminha a busca para outros pares
        # 'list(self.super_peers)' cria uma cópia para iterar com segurança
        for peer in list(self.super_peers):
            # NÃO encaminha a busca de volta para quem a enviou
            if peer == except_locator:
                continue
            try:
                # Este servidor (central) age como CLIENTE de outro servidor central
                channel = grpc.insecure_channel(peer)
                stub = kv_pb2_grpc.CentralServiceStub(channel)
                
                # Prepara a requisição de encaminhamento
                # Passa o 'self.locator' para que o próximo par não pergunte de volta
                forward_req = kv_pb2.SearchRequest(key=key, except_=self.locator)
                
                # Faz a chamada RPC recursiva
                resp = stub.Search(forward_req, timeout=2)
                if resp.locator:
                    # Se o par encontrou, retorna a resposta imediatamente
                    return kv_pb2.SearchReply(locator=resp.locator)
            except Exception:
                # Se um par falhar (ex: timeout, offline), apenas continua para o próximo
                continue
        
        # Se ninguém na rede encontrou, retorna ""
        return kv_pb2.SearchReply(locator="")

    # Implementação do RPC 'Pairing' (Parte 3)
    def Pairing(self, request, context):
        # Se não estiver em modo super-par (Parte 2), não faz nada e retorna 0
        if self.super_peers is None:
            return kv_pb2.PairingReply(result=0)

        # Se estiver em modo super-par, adiciona o locator à lista de pares
        with self.lock:
            if request.locator not in self.super_peers:
                self.super_peers.append(request.locator)

        return kv_pb2.PairingReply(result=1)

    # Implementação do RPC 'Terminate'
    def Terminate(self, request, context):
        with self.lock:
            # Conta o número total de chaves registradas
            total = len(self.directory)

        # Sinaliza o evento de parada (libera o 'stop_event.wait()' na 'serve()')
        self.stop_event.set()
        return kv_pb2.TerminateReply(total=total)

def serve():
    # Verifica o número de argumentos para determinar o modo de operação
    # Parte 2: svc_cen.py PORTA (len(sys.argv) == 2)
    # Parte 3: svc_cen.py PORTA [flag] (len(sys.argv) == 3)
    port = sys.argv[1]
    super_mode = (len(sys.argv) == 3)

    # Cria o evento de parada
    stop_event = threading.Event()
    
    # Configura o servidor gRPC
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    
    # Instancia o Servicer, passando a porta e o modo de operação
    servicer = CentralServicer(stop_event, port, super_mode)
    
    # Adiciona o Servicer ao servidor
    kv_pb2_grpc.add_CentralServiceServicer_to_server(servicer, server)
    
    # Faz o bind na porta (escutando em todas as interfaces)
    server.add_insecure_port(f"[::]:{port}")
    server.start()
    
    # Bloqueia a thread principal até o 'Terminate' ser chamado
    stop_event.wait()
    
    # Desliga o servidor
    server.stop(0).wait(5)


if __name__ == "__main__":
    serve()