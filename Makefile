CXXFLAGS = -Wall -Wextra -Werror -std=c++14 -pedantic -O2
LDFLAGS  = -lstdc++ -lm

SOURCES  = noq.cc lib.cc
OBJECTS  = $(SOURCES:.cc=.o)

.PHONY: all test options clean weather

all: options noq

test: CXXFLAGS += -DTEST
test: all

options:
	@echo Build options:
	@echo "CXX      = $(CXX)"
	@echo "CXXFLAGS = $(CXXFLAGS)"
	@echo "LDFLAGS  = $(LDFLAGS)"

weather:
	cat data/TG_SOUID171642.txt \
		| awk -f script/filter.awk \
		| awk -f script/gen-weather.awk \
		> weather.h

noq: $(OBJECTS)
noq.o: weather.h

clean:
	rm -f noq $(OBJECTS)
