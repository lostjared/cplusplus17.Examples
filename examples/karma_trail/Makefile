OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

CFLAGS= -std=c++17
LDFLAGS=

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

per.test: $(OBJ)
	$(CXX) -o karma-trail $(OBJ) $(LDFLAGS)

all: example

.PHONY: clean clear
clean:
	rm -f karma-trail *.o
