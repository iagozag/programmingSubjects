#!/usr/bin/env python3
import sys
import grpc
import kv_pb2
import kv_pb2_grpc


if __name__ == "__main__":
    locator = sys.argv[1]
    channel = grpc.insecure_channel(locator)
    stub = kv_pb2_grpc.CentralServiceStub(channel)

    for raw in sys.stdin:
        line = raw.rstrip('\n')

        if not line:
            continue

        if line == 'T':
            resp = stub.Terminate(kv_pb2.TerminateRequest())
            print(resp.total)
            break

        elif line.startswith('P '):
            try:
                _, loc = line.split(' ', 1)
                resp = stub.Pairing(kv_pb2.PairingRequest(locator=loc.strip()))
                print(resp.result)
            except Exception:
                continue

        elif line.startswith('B '):
            try:
                _, chs = line.split(' ', 1)
                ch = int(chs.strip())
                resp = stub.Search(kv_pb2.SearchRequest(key=ch, except_=""))
                if resp.locator:
                    print(f"{resp.locator}=", end="")
                    try:
                        pch = grpc.insecure_channel(resp.locator)
                        pstub = kv_pb2_grpc.PairServiceStub(pch)

                        qresp = pstub.Query(kv_pb2.QueryRequest(key=ch), timeout=5)
                        print(qresp.value)
                    except Exception:
                        print("")
            except Exception:
                continue

        else:
            continue
