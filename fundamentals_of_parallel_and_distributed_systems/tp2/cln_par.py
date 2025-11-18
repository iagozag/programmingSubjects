#!/usr/bin/env python3
import sys
import grpc
import kv_pb2
import kv_pb2_grpc

if __name__ == "__main__":
    locator = sys.argv[1]
    channel = grpc.insecure_channel(locator)
    stub = kv_pb2_grpc.PairServiceStub(channel)

    for raw in sys.stdin:
        line = raw.rstrip("\n")
        if not line:
            continue
        if line.startswith('I '):
            try:
                _prefix, rest = line.split(' ', 1)
                ch_str, val = rest.split(' ', 1)
                ch = int(ch_str)
                resp = stub.Insert(kv_pb2.InsertRequest(key=ch, value=val))
                print(resp.result)
            except Exception:
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
            continue
