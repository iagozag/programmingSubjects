CC :=g++
BUILDDIR := build
CFLAGS :=-g -Wall -O3 -std=c++20
TARGET := vpl_execution
INC := -I include/

all: $(TARGET)

$(BUILDDIR)/Pessoa.o: src/entidades/Pessoa.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ src/entidades/Pessoa.cpp

$(BUILDDIR)/Funcionario.o: src/entidades/Funcionario.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ src/entidades/Funcionario.cpp

$(BUILDDIR)/Professor.o: src/entidades/Professor.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ src/entidades/Professor.cpp

$(BUILDDIR)/main.o: src/main.cpp
	@mkdir -p $(BUILDDIR)
	$(CC) $(CFLAGS) $(INC) -c -o $@ src/main.cpp

$(TARGET): $(BUILDDIR)/Pessoa.o $(BUILDDIR)/Funcionario.o $(BUILDDIR)/Professor.o $(BUILDDIR)/main.o
	$(CC) $^ -o $(TARGET)

clean:
	rm -f $(BUILDDIR)/*.o vpl_execution

.PHONY: clean
