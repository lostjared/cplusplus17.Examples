OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
PROGRAM=dmd-example
CFLAGS= -std=c++17 -O2
LDFLAGS=

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

$(PROGRAM): $(OBJ)
	$(CXX) -o $(PROGRAM) $(OBJ) $(LDFLAGS)

all: $(PROGRAM)

.PHONY: clean
clean:
	rm -f $(PROGRAM) *.o
install: $(PROGRAM)
	cp $(PROGRAM) /usr/local/bin
