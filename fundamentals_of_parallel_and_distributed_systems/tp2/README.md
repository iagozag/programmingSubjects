# KV Distributed - como usar

1. Gere os stubs:

```bash
make stubs
```

2. Execute um servidor central (porta 6666):

```bash
make run_serv_central arg=6666
# ou
python3 svc_cen.py 6666
```

3. Execute um servidor de pares (porta 5555) que registra no central em `localhost:6666`:

```bash
make run_serv_pares_2 arg1=5555 arg2=localhost:6666
# ou
python3 svc_par.py 5555 localhost:6666
```

4. Em outro terminal, execute o cliente do par:

```bash
make run_cli_pares arg=localhost:5555
# ou
python3 cln_par.py localhost:5555
```

5. Exemplos de comandos para `cln_par` (stdin):

```
I 1 valor com espaços
C 1
A
T
```

6. Exemplos de comandos para `cln_cen` (stdin):

```
B 1       # procura chave 1: se encontrada imprime locator=valor
P somehost:port
T
```

Observações: certifique-se de não deixar `print()`s extras nos servidores — apenas os clientes devem escrever na saída conforme especificado.
