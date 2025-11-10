#!/usr/bin/env python3
import sys
import grpc
import kv_pb2
import kv_pb2_grpc

def usage():
    print("uso: cln_par.py host:port")
    sys.exit(1)

if __name__ == "__main__":
    if len(sys.argv) != 2:
        usage()
    locator = sys.argv[1]
    channel = grpc.insecure_channel(locator)
    stub = kv_pb2_grpc.PairServiceStub(channel)

    for raw in sys.stdin:
        line = raw.rstrip("\n")
        if not line:
            continue
        if line.startswith('I '):
            # I ch valor (valor pode conter espaços)
            try:
                _prefix, rest = line.split(' ', 1)
                ch_str, val = rest.split(' ', 1)
                ch = int(ch_str)
                resp = stub.Insert(kv_pb2.InsertRequest(key=ch, value=val))
                print(resp.result)
            except Exception:
                # se a linha não estiver bem formada, ignore
                continue
        elif line.startswith('C '):
            try:
                _prefix, chs = line.split(' ', 1)
                ch = int(chs.strip())
                resp = stub.Query(kv_pb2.QueryRequest(key=ch))
                print(resp.value)
            except Exception:
                continue
        elif line == 'A':
            resp = stub.Activate(kv_pb2.ActivateRequest())
            print(resp.result)
        elif line == 'T':
            resp = stub.Terminate(kv_pb2.TerminateRequest())
            print(resp.total)
            break
        else:
            # ignora qualquer outra linha
            continue
