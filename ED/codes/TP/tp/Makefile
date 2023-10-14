CC = g++
LIBS = -lm
SRC = src
SRCEXT = cpp
OBJ = obj
INC = include
BIN = bin
CFLAGS = -pg -g -Wall -c -I$(INC)
EXE = $(BIN)/tp1.out

SOURCES := $(shell find $(SRC) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRC)/%,$(OBJ)/%,$(SOURCES:.$(SRCEXT)=.o))

all: $(EXE)

mem: $(EXE)
	if test -d /tmp/out; then rm -rf /tmp/out; fi
	mkdir /tmp/out
	mkdir /tmp/out/teste
	fixaddr/fixaddr.csh teste/somalog.out /tmp/out
	$(ANALISAMEM) -i teste/somalog.out -p /tmp/out/soma
	fixaddr/fixaddr.csh teste/internolog.out /tmp/out
	$(ANALISAMEM) -i teste/internolog.out -p /tmp/out/interno
	fixaddr/fixaddr.csh teste/normalog.out /tmp/out
	$(ANALISAMEM) -i teste/normalog.out -p /tmp/out/norma
	gnuplot /tmp/out/*.gp
	ls /tmp/out/

$(EXE): $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) $(LIBS)
	@echo ""

$(OBJ)/%.o: $(SRC)/%.$(SRCEXT)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXE) $(OBJECTS)

.PHONY: clean

