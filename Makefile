CXX      ?= g++
CXXFLAGS ?= -O2 -Wall `pkg-config lua5.1 --cflags`
LDFLAGS  ?= `pkg-config lua5.1 --libs`

.SUFFIXES: .cpp

all: main

clean:
	rm -rf ./main

main: main.cpp
	$(CXX) $(CXXFLAGS) -o main main.cpp $(LDFLAGS)
