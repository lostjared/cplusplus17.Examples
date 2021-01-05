OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

CFLAGS= -std=c++17
LDFLAGS=

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

per.test: $(OBJ)
	$(CXX) -o per.test $(OBJ) $(LDFLAGS)

all: example

.PHONY: clean clear
clean:
	rm -f per.test *.o 
clear:
	rm -f *.dat
