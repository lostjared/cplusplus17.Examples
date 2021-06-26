OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
PROGRAM=transform-ex
CFLAGS= -std=c++17
LDFLAGS=

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

per.test: $(OBJ)
	$(CXX) -o $(PROGRAM) $(OBJ) $(LDFLAGS)

all: example

.PHONY: clean clear
clean:
	rm -f $(PROGRAM) *.o
