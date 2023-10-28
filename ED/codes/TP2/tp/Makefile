CC = g++
LIBS = -lm
SRC = src
SRCEXT = cpp
OBJ = obj
INC = include
BIN = bin
CFLAGS = -pg -g -Wall -c -I$(INC)
EXE = $(BIN)/tp2.out
ANALISAMEM = ../analisamem/bin/analisamem

SOURCES := $(shell find $(SRC) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRC)/%,$(OBJ)/%,$(SOURCES:.$(SRCEXT)=.o))

all: test

mem: $(EXE)
	if test -d /tmp/out; then rm -rf /tmp/out; fi
	mkdir /tmp/out
	mkdir /tmp/out/teste
	fixaddr/fixaddr.csh teste/evaluatelog.out /tmp/out
	$(ANALISAMEM) -i teste/evaluatelog.out -p /tmp/out/evaluate
	fixaddr/fixaddr.csh teste/satisfiabilitylog.out /tmp/out
	$(ANALISAMEM) -i teste/satisfiabilitylog.out -p /tmp/out/satisfiability
	gnuplot /tmp/out/*.gp
	ls /tmp/out/

test: $(EXE)

$(EXE): $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) $(LIBS)
	@echo ""

$(OBJ)/%.o: $(SRC)/%.$(SRCEXT)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXE) $(OBJECTS) gmon.out

.PHONY: clean

