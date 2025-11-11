CC := g++
SRCDIR := src
BUILDDIR := build
TARGET := main

SRCEXT := cpp
SOURCES := $(shell find $(SRCDIR) -type f -name *.$(SRCEXT))
OBJECTS := $(patsubst $(SRCDIR)/%,$(BUILDDIR)/%,$(SOURCES:.$(SRCEXT)=.o))
CFLAGS := -fsanitize=address,undefined -fno-omit-frame-pointer -g -Wall -O3 -Wshadow -std=c++20 -Wno-unused-result -Wno-sign-compare -Wno-char-subscripts
LDFLAGS := -fsanitize=address,undefined -lgmp -lgmpxx
INC := -I include/ -I third_party/

$(TARGET): $(OBJECTS)
	$(CC) $(LDFLAGS) $^ -o $(TARGET)

$(BUILDDIR)/%.o: $(SRCDIR)/%.$(SRCEXT)
	@mkdir -p $(@D)
	$(CC) $(CFLAGS) $(INC) -c -o $@ $<

clean:
	$(RM) -r $(BUILDDIR)/* $(TARGET)

.PHONY: clean
