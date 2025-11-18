PY=python3
PROTO=kv.proto
PY_FILES := kv_pb2.py kv_pb2_grpc.py

all: stubs

clean:
	rm -f $(PY_FILES) *.pyc *.zip

# REGRA STUBS CORRIGIDA (AGORA EM DUAS PARTES)
stubs: $(PY_FILES)

$(PY_FILES): $(PROTO)
	$(PY) -m pip install --user grpcio grpcio-tools protobuf >/dev/null 2>&1 || true
	$(PY) -m grpc_tools.protoc -I. --python_out=. --grpc_python_out=. $(PROTO)

run_cli_pares: stubs
	$(PY) cln_par.py $(arg)

run_serv_pares_1: stubs
	$(PY) svc_par.py $(arg)

run_serv_pares_2: stubs
	$(PY) svc_par.py $(arg1) $(arg2)

run_serv_central: stubs
	$(PY) svc_cen.py $(arg)

run_cli_central: stubs
	$(PY) cln_cen.py $(arg)

# REGRA RUN_SUPER_PAR CORRIGIDA (USA $(arg))
run_super_par: stubs
	$(PY) svc_cen.py $(arg) super