OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

OUTPUT=var-ex
CFLAGS= -std=c++17
LDFLAGS=

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

$(OUTPUT): $(OBJ)
	$(CXX) -o $(OUTPUT) $(OBJ) $(LDFLAGS)

all: example

.PHONY: clea
clean:
	rm -f $(OUTPUT)  *.o
