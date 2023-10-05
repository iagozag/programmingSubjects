CC = g++
LIBS = -lm
SRC = src
SRCEXT = cpp
OBJ = obj
INC = include
BIN = bin
CFLAGS = -pg -Wall -c -I$(INC)
EXE = $(BIN)/main

SOURCES := $(shell find $(SRC) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRC)/%,$(OBJ)/%,$(SOURCES:.$(SRCEXT)=.o))

NUMBER = 20
TIMES = 10000000

comp: $(EXE)

pref: $(EXE)
	$(EXE) fati 5 1 /tmp/analisefatigprof.out
	@echo ""
	$(EXE) fatr 5 1 /tmp/analisefatrgprof.out
	@echo ""
	$(EXE) fibi 5 1 /tmp/analisefibigprof.out
	@echo ""
	$(EXE) fibr 5 1 /tmp/analisefibrgprof.out
	@echo ""

gprof: $(EXE)
	$(EXE) fati $(NUMBER) $(TIMES) /tmp/analisefatigprof.out
	gprof $(EXE) gmon.out > /tmp/analisefatigprof.txt
	@echo ""
	$(EXE) fatr $(NUMBER) $(TIMES) /tmp/analisefatrgprof.out
	gprof $(EXE) gmon.out > /tmp/analisefatrgprof.txt
	@echo ""
	$(EXE) fibi $(NUMBER) $(TIMES) /tmp/analisefibigprof.out
	gprof $(EXE) gmon.out > /tmp/analisefibigprof.txt
	@echo ""
	$(EXE) fibr $(NUMBER) $(TIMES) /tmp/analisefibrgprof.out
	gprof $(EXE) gmon.out > /tmp/analisefibrgprof.txt
	@echo ""

$(EXE): $(OBJECTS)
	$(CC) -pg -o $(EXE) $(OBJECTS) $(LIBS)
	@echo ""

$(OBJ)/%.o: $(SRC)/%.$(SRCEXT)
	$(CC) $(CFLAGS) -o $@ $<

run: pref

test: comp

clean:
	rm -f $(EXE) $(OBJECTS) gmon.out

.PHONY: clean
