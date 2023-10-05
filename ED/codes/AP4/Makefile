#---------------------------------------------------------------------
# Arquivo	: Makefile
# Conteúdo	: compilar o programa matop
# Autor		: Wagner Meira Jr. (meira@dcc.ufmg.br)
# Histórico	: 2021-10-18 - arquivo criado
#		: 2021-10-21 - estrutura de diretórios
#               : 2021-11-15 - Versao 1.1 memlog
#---------------------------------------------------------------------
# Opções	: make all - compila tudo
#               : make mem - gera arquivos de registro de acesso
#               : make prof - faz medidas de tempo de desempenho
#               : make gprof - ilustra uso do gprof para depuração
#		: make clean - remove objetos e executável
#---------------------------------------------------------------------

CC = gcc
LIBS = -lm
SRC = src
OBJ = obj
INC = include
BIN = bin
OBJS = $(OBJ)/matop.o $(OBJ)/mat.o 
HDRS = $(INC)/mat.h $(INC)/msgassert.h
CFLAGS = -g -Wall -c -I$(INC)

EXE = $(BIN)/matop

all: $(EXE)

perf: $(EXE)
	$(EXE) -s -x 100 -y 100 > /tmp/soma100.out
	$(EXE) -m -x 100 -y 100 > /tmp/mult100.out
	$(EXE) -t -x 100 -y 100 > /tmp/transp100.out
	$(EXE) -s -x 200 -y 200 > /tmp/soma200.out
	$(EXE) -m -x 200 -y 200 > /tmp/mult200.out
	$(EXE) -t -x 200 -y 200 > /tmp/transp200.out
	$(EXE) -s -x 300 -y 300 > /tmp/soma300.out
	$(EXE) -m -x 300 -y 300 > /tmp/mult300.out
	$(EXE) -t -x 300 -y 300 > /tmp/transp300.out
	$(EXE) -s -x 400 -y 400 > /tmp/soma400.out
	$(EXE) -m -x 400 -y 400 > /tmp/mult400.out
	$(EXE) -t -x 400 -y 400 > /tmp/transp400.out
	$(EXE) -s -x 500 -y 500 > /tmp/soma500.out
	$(EXE) -m -x 500 -y 500 > /tmp/mult500.out
	$(EXE) -t -x 500 -y 500 > /tmp/transp500.out
	$(EXE) -m -x 100 -y 100 > /tmp/mult100log.out

gprof: $(BIN)/matop
	$(EXE) -s -x 500 -y 500 > /tmp/soma500gprof.out
	gprof $(EXE) gmon.out > /tmp/soma500gprof.txt
	$(EXE) -m  -x 500 -y 500 > /tmp/mult500gprof.out
	gprof $(EXE) gmon.out > /tmp/mult500gprof.txt
	$(EXE) -t -x 500 -y 500 > /tmp/transp500gprof.out
	gprof $(EXE) gmon.out > /tmp/transp500gprof.txt

$(BIN)/matop: $(OBJS)
	$(CC) -g -o $(BIN)/matop $(OBJS) $(LIBS)

$(OBJ)/matop.o: $(HDRS) $(SRC)/matop.c
	$(CC) $(CFLAGS) -o $(OBJ)/matop.o $(SRC)/matop.c 

$(OBJ)/mat.o: $(HDRS) $(SRC)/mat.c
	$(CC) $(CFLAGS) -o $(OBJ)/mat.o $(SRC)/mat.c 
	
clean:
	rm -f $(EXE) $(OBJS) gmon.out
