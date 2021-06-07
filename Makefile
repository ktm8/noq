CXXFLAGS = -Wall -Wextra -Werror -std=c++14 -pedantic -O3
LDFLAGS  = -lstdc++ -lm

SOURCES  = noq.cc lib.cc
OBJECTS  = $(SOURCES:.cc=.o)

.PHONY: all clean

all: options noq

options:
	@echo Build options:
	@echo "CXX      = $(CXX)"
	@echo "CXXFLAGS = $(CXXFLAGS)"
	@echo "LDFLAGS  = $(LDFLAGS)"

noq: $(OBJECTS)

clean:
	rm -f noq $(OBJECTS)
