EXEC = main

CC = g++
CFLAGS = -Wall -Wextra -O2 -std=c++17

SRC = main.cpp passa_tempo.cpp
OBJ = $(SRC:.cpp=.o)

all: build

build: $(EXEC)

$(EXEC): $(OBJ)
	$(CC) $(CFLAGS) -o $@ $^

run: build
	./$(EXEC)

clean:
	rm -f $(EXEC) $(OBJ) *~

%.o: %.cpp
	$(CC) $(CFLAGS) -c $< -o $@
