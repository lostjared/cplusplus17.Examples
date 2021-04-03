OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
PROGRAM=c-style
CFLAGS= -std=c++17
LDFLAGS=

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

$(PROGRAM): $(OBJ)
	$(CXX) -o $(PROGRAM) $(OBJ) $(LDFLAGS)

all: example

.PHONY: clean
clean:
	rm -f $(PROGRAM) *.o
