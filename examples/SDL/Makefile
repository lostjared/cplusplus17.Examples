OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
PROGRAM=sdl-ex
CFLAGS= -std=c++17 `pkg-config sdl2 --cflags`
LDFLAGS= `pkg-config sdl2 --libs`

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

$(PROGRAM): $(OBJ)
	$(CXX) -o $(PROGRAM) $(OBJ) $(LDFLAGS)

all: $(PROGRAM)

.PHONY: clean
clean:
	rm -f $(PROGRAM) *.o
