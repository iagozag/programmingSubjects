#!/usr/bin/env python3
import sys
import threading
import socket
from concurrent import futures

import grpc
import kv_pb2
import kv_pb2_grpc


class CentralServicer(kv_pb2_grpc.CentralServiceServicer):
    def __init__(self, stop_event, port, super_mode=False):
        self.lock = threading.Lock()
        self.directory = {}
        self.super_peers = [] if super_mode else None
        self.stop_event = stop_event
        self.port = port
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
        
        except_locator = request.except_
        
        with self.lock:
            loc = self.directory.get(key, "")
        if loc:
            return kv_pb2.SearchReply(locator=loc)
        
        if self.super_peers is None:
            return kv_pb2.SearchReply(locator="")
        
        for peer in list(self.super_peers):
            if peer == except_locator:
                continue
            try:
                channel = grpc.insecure_channel(peer)
                stub = kv_pb2_grpc.CentralServiceStub(channel)
                
                forward_req = kv_pb2.SearchRequest(key=key, except_=self.locator)
                
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
        return kv_pb2.PairingReply(result=1)

    def Terminate(self, request, context):
        with self.lock:
            total = len(self.directory)
        self.stop_event.set()
        return kv_pb2.TerminateReply(total=total)

def serve():
    port = sys.argv[1]
    super_mode = (len(sys.argv) == 3)

    stop_event = threading.Event()
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    
    servicer = CentralServicer(stop_event, port, super_mode)
    
    kv_pb2_grpc.add_CentralServiceServicer_to_server(servicer, server)
    server.add_insecure_port(f"[::]:{port}")
    server.start()
    stop_event.wait()
    server.stop(0).wait(5)


if __name__ == "__main__":
    serve()