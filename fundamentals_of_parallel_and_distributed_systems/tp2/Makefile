PY=python3
PROTO=kv.proto
PY_FILES := kv_pb2.py kv_pb2_grpc.py

all: stubs

clean:
	rm -f $(PY_FILES) *.pyc __pycache__ *.zip

stubs:
	$(PY) -m pip install --user grpcio grpcio-tools protobuf >/dev/null 2>&1 || true
	$(PY) -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. $(PROTO)

run_cli_pares:
	$(PY) cln_par.py $(arg)

run_serv_pares_1:
	$(PY) svc_par.py $(arg)

run_serv_pares_2:
	$(PY) svc_par.py $(arg1) $(arg2)

run_serv_central:
	$(PY) svc_cen.py $(arg)

run_cli_central:
	$(PY) cln_cen.py $(arg)

run_super_par:
	$(PY) svc_cen.py $(arg1) super
