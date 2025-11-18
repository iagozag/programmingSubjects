#!/usr/bin/env python3
import sys
import threading
import socket
from concurrent import futures

import grpc
import kv_pb2
import kv_pb2_grpc

# Define a classe do "Servidor de Pares"
# Esta classe implementa os serviços definidos no kv.proto
class PairServicer(kv_pb2_grpc.PairServiceServicer):
    
    # Construtor do servidor
    def __init__(self, stop_event, central_locator=None, port=None):
        self.store = {}  # Dicionário para armazenar os pares (chave, valor)
        self.lock = threading.Lock()  # Lock para proteger o dicionário contra concorrência
        self.stop_event = stop_event  # Evento para sinalizar o término do servidor
        
        # 'central_locator' e 'port' serão None na Parte 1
        # Na Parte 2, eles são preenchidos e usados pelo 'Activate'
        self.central_locator = central_locator
        self.port = port

    # Implementação do RPC 'Insert'
    def Insert(self, request, context):
        key = int(request.key)
        value = request.value[:1024]  # Garante o limite de 1024 caracteres

        with self.lock:  # Adquire o lock para modificar o 'store'
            existed = key in self.store  # Verifica se a chave já existe
            self.store[key] = value  # Insere ou atualiza o valor

        # Retorna 1 se a chave foi atualizada, 0 se foi uma nova inserção
        return kv_pb2.InsertReply(result=1 if existed else 0)

    # Implementação do RPC 'Query'
    def Query(self, request, context):
        key = int(request.key)

        with self.lock:  # Adquire o lock para ler o 'store'
            # Retorna o valor associado à chave, ou "" (string nula) se não existir
            v = self.store.get(key, "")

        return kv_pb2.QueryReply(value=v)

    # Implementação do RPC 'Activate'
    def Activate(self, request, context):
        # Se 'central_locator' não foi fornecido (Parte 1), não faz nada.
        if not self.central_locator:
            return kv_pb2.ActivateReply(result=0)

        # ----- Comportamento da Parte 2: Registrar-se no servidor central -----
        
        # 1. Monta o próprio locator (ex: "xingu.grad.dcc.ufmg.br:5555")
        #    socket.getfqdn() obtém o nome completo da máquina.
        locator = f"{socket.getfqdn()}:{self.port}"
        
        with self.lock:
            # 2. Pega a lista de todas as chaves que armazena atualmente
            keys = list(self.store.keys())

        try:
            # 3. Este servidor (de pares) agora age como um CLIENTE
            #    do servidor central para se registrar.
            channel = grpc.insecure_channel(self.central_locator)
            stub = kv_pb2_grpc.CentralServiceStub(channel)
            
            # 4. Prepara a requisição de Registro
            req = kv_pb2.RegisterRequest(locator=locator, keys=keys)
            
            # 5. Chama o RPC 'Register' do servidor central
            resp = stub.Register(req, timeout=5)

            # Retorna o número de chaves processadas pelo servidor central
            return kv_pb2.ActivateReply(result=resp.processed)
        except Exception:
            # Em caso de falha na comunicação com o central, retorna 0
            return kv_pb2.ActivateReply(result=0)

    # Implementação do RPC 'Terminate'
    def Terminate(self, request, context):
        with self.lock:
            total = len(self.store)  # Conta o número de chaves armazenadas

        # Sinaliza o evento de parada. Isso fará o 'stop_event.wait()'
        # na função 'serve()' ser desbloqueado, permitindo o desligamento.
        self.stop_event.set()
        return kv_pb2.TerminateReply(total=total)

def serve():
    # Verifica o número de argumentos para determinar o modo de operação
    # Parte 1: svc_par.py PORTA (len(sys.argv) == 2)
    # Parte 2: svc_par.py PORTA LOCATOR_CENTRAL (len(sys.argv) == 3)
    port = sys.argv[1]
    central_locator = sys.argv[2] if len(sys.argv) == 3 else None

    # Cria o evento de parada que será passado ao Servicer
    stop_event = threading.Event()
    
    # Configura o servidor gRPC com um pool de 10 threads
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    
    # Instancia o Servicer, passando os argumentos necessários
    servicer = PairServicer(stop_event, central_locator, port)
    kv_pb2_grpc.add_PairServiceServicer_to_server(servicer, server)

    # Define o endereço de bind. '[::]' (ou '0.0.0.0') escuta em todas
    # as interfaces de rede, não apenas localhost.
    bind_addr = f"[::]:{port}"
    server.add_insecure_port(bind_addr)
    
    # Inicia o servidor (não bloqueante)
    server.start()
    
    # Loop principal do servidor: bloqueia a thread principal
    # até que o 'stop_event' seja sinalizado (pelo RPC 'Terminate')
    stop_event.wait()
    
    # Inicia o processo de desligamento gracioso do servidor
    server.stop(0).wait(5)

if __name__ == "__main__":
    serve()