CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := main

# CPLEX_HOME    = /opt/ibm/ILOG/CPLEX_Studio2212/cplex
# CONCERT_HOME  = /opt/ibm/ILOG/CPLEX_Studio2212/concert
CPLEX_HOME  = ~/cplex/cplex
CONCERT_HOME = ~/cplex/concert

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))

CFLAGS := -fno-omit-frame-pointer -Wall -O3 -g -Wshadow -std=c++17 \
          -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts

CPLEXFLAGS := -I $(CPLEX_HOME)/include -I $(CONCERT_HOME)/include -m64 -DIL_STD

LDFLAGS := -L $(CPLEX_HOME)/lib/x86-64_linux/static_pic \
           -L $(CONCERT_HOME)/lib/x86-64_linux/static_pic

LDLIBS := -lilocplex -lcplex -lconcert -lpthread -ldl

INC := -I include/

$(TARGET): $(OBJECTS)
	$(CC) $(CFLAGS) $^ -o $(TARGET) $(LDFLAGS) $(LDLIBS)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(CPLEXFLAGS) $(INC) -c -o $@ $<

# Run with default seed 42
test: $(TARGET)
	./$(TARGET) 42

# Run with a custom seed: make run SEED=123
run: $(TARGET)
	./$(TARGET) $(SEED)

clean:
	$(RM) -r $(BUILDDIR)/* $(TARGET)

.PHONY: clean test run
