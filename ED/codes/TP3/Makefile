CC = g++
LIBS = -lm
SRC = src
SRCEXT = cpp
OBJ = obj
INC = include
BIN = bin
CFLAGS = -g -Wall -c -I$(INC)
EXE = $(BIN)/tp3.out

SOURCES := $(shell find $(SRC) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRC)/%,$(OBJ)/%,$(SOURCES:.$(SRCEXT)=.o))

all: $(EXE)
	more vpl_evaluate.cases

$(EXE): $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) $(LIBS)
	@echo ""

$(OBJ)/%.o: $(SRC)/%.$(SRCEXT)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXE) $(OBJECTS) gmon.out

.PHONY: clean

