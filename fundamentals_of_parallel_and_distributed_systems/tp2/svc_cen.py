#!/usr/bin/env python3
import sys
import threading
import socket  # <-- 1. Importado
from concurrent import futures

import grpc
import kv_pb2
import kv_pb2_grpc


class CentralServicer(kv_pb2_grpc.CentralServiceServicer):
    def __init__(self, stop_event, port, super_mode=False):  # <-- 2. Recebe a porta
        self.lock = threading.Lock()
        self.directory = {}   # key:int -> locator:str
        self.super_peers = [] if super_mode else None
        self.stop_event = stop_event
        self.port = port
        # 3. Armazena o próprio locator para evitar loops
        self.locator = f"{socket.getfqdn()}:{self.port}" if super_mode else ""

    def Register(self, request, context):
        processed = 0
        with self.lock:
            for k in request.keys:
                self.directory[int(k)] = request.locator
                processed += 1
        return kv_pb2.RegisterReply(processed=processed)

    def Search(self, request, context):
        key = int(request.key)
        except_locator = request.exc if hasattr(request, 'except') else ""
        with self.lock:
            loc = self.directory.get(key, "")
        if loc:
            return kv_pb2.SearchReply(locator=loc)
        
        # se não há loc e não estamos em modo super, retorna vazio
        if self.super_peers is None:
            return kv_pb2.SearchReply(locator="")
        
        # modo super -> propaga para super_peers exceto o que pediu
        for peer in list(self.super_peers):
            if peer == except_locator:
                continue
            try:
                channel = grpc.insecure_channel(peer)
                stub = kv_pb2_grpc.CentralServiceStub(channel)
                
                # 4. CORREÇÃO: Passa 'self.locator' no campo 'except'
                forward_req = kv_pb2.SearchRequest(key=key, except=self.locator)
                
                resp = stub.Search(forward_req, timeout=2)
                if resp.locator:
                    return kv_pb2.SearchReply(locator=resp.locator)
            except Exception:
                continue
        return kv_pb2.SearchReply(locator="")

    def Pairing(self, request, context):
        if self.super_peers is None:
            return kv_pb2.PairingReply(result=0)
        with self.lock:
            if request.locator not in self.super_peers:
                self.super_peers.append(request.locator)
        return kv_pb2.PairingReply(result=0)

    def Terminate(self, request, context):
        with self.lock:
            total = len(self.directory)
        self.stop_event.set()
        return kv_pb2.TerminateReply(total=total)

def serve():
    if not (2 <= len(sys.argv) <= 3):
        print("uso: svc_cen.py PORT [super_flag]", file=sys.stderr)
        sys.exit(1)
    port = sys.argv[1]
    super_mode = (len(sys.argv) == 3)

    stop_event = threading.Event()
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    
    # 2. Passa a porta para o construtor do servicer
    servicer = CentralServicer(stop_event, port, super_mode)
    
    kv_pb2_grpc.add_CentralServiceServicer_to_server(servicer, server)
    server.add_insecure_port(f"[::]:{port}")
    server.start()
    stop_event.wait()
    server.stop(0).wait(5)


if __name__ == "__main__":
    serve()