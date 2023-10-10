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

test:
	$(EXE) -s "0 | 1 & 2" 0e0
	$(EXE) -s "0 | 1 & 2" e00
	$(EXE) -s "0 | 1 & 2" e11
	$(EXE) -s "(0 | 1)" ea
	$(EXE) -a "~ ~ 0 | 1" 10
	$(EXE) -s "0 | ~ ~ 1" ea
	$(EXE) -a "~ ~ ~ 0 | 1" 10
	$(EXE) -a "~ ~ ~ ~ 0 | 1" 10
	$(EXE) -s "(0 & 1) | (2 & 3 & 4)" e0a11
	$(EXE) -s "0 | 1 | 2" aae
	$(EXE) -s "0 | 1 | 2" eaa

$(EXE): $(OBJECTS)
	$(CC) -o $(EXE) $(OBJECTS) $(LIBS)
	@echo ""

$(OBJ)/%.o: $(SRC)/%.$(SRCEXT)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXE) $(OBJECTS)

.PHONY: clean

