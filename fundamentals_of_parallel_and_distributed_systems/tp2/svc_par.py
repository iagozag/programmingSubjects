#!/usr/bin/env python3
import sys
import threading
import socket
from concurrent import futures

import grpc
import kv_pb2
import kv_pb2_grpc


class PairServicer(kv_pb2_grpc.PairServiceServicer):
    def __init__(self, stop_event, central_locator=None, port=None):
        self.store = {}
        self.lock = threading.Lock()
        self.stop_event = stop_event
        self.central_locator = central_locator
        self.port = port

    def Insert(self, request, context):
        key = int(request.key)
        value = request.value[:1024]
        with self.lock:
            existed = key in self.store
            self.store[key] = value
        return kv_pb2.InsertReply(result=1 if existed else 0)

    def Query(self, request, context):
        key = int(request.key)
        with self.lock:
            v = self.store.get(key, "")
        return kv_pb2.QueryReply(value=v)

    def Activate(self, request, context):
        if not self.central_locator:
            return kv_pb2.ActivateReply(result=0)

        locator = f"{socket.getfqdn()}:{self.port}"
        with self.lock:
            keys = list(self.store.keys())
        try:
            channel = grpc.insecure_channel(self.central_locator)
            stub = kv_pb2_grpc.CentralServiceStub(channel)
            req = kv_pb2.RegisterRequest(locator=locator, keys=keys)
            resp = stub.Register(req, timeout=5)
            return kv_pb2.ActivateReply(result=resp.processed)
        except Exception:
            return kv_pb2.ActivateReply(result=0)

    def Terminate(self, request, context):
        with self.lock:
            total = len(self.store)
        self.stop_event.set()
        return kv_pb2.TerminateReply(total=total)

def serve():
    if not (2 <= len(sys.argv) <= 3):
        print("uso: svc_par.py PORT [central_locator]", file=sys.stderr)
        sys.exit(1)
    port = sys.argv[1]
    central_locator = sys.argv[2] if len(sys.argv) == 3 else None

    stop_event = threading.Event()
    server = grpc.server(futures.ThreadPoolExecutor(max_workers=10))
    servicer = PairServicer(stop_event, central_locator, port)
    kv_pb2_grpc.add_PairServiceServicer_to_server(servicer, server)
    bind_addr = f"[::]:{port}"
    server.add_insecure_port(bind_addr)
    server.start()
    stop_event.wait()
    server.stop(0).wait(5)

if __name__ == "__main__":
    serve()
