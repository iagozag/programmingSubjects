CC = gcc
LIBS = -lm
SRC = src
SRCEXT = c
OBJ = obj
INC = include
BIN = bin
CFLAGS = -g -pg -Wall -c -I$(INC)
EXE = $(BIN)/pa9.out

SOURCES := $(shell find $(SRC) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRC)/%,$(OBJ)/%,$(SOURCES:.$(SRCEXT)=.o))

all: $(EXE)

$(EXE): $(OBJECTS)
	$(CC) -pg -o $(EXE) $(OBJECTS) $(LIBS)
	@echo ""

$(OBJ)/%.o: $(SRC)/%.$(SRCEXT)
	$(CC) $(CFLAGS) -o $@ $<

clean:
	rm -f $(EXE) $(OBJECTS)

.PHONY: clean

