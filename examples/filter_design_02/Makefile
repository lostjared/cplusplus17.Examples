OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
PROGRAM=dmd-example
CFLAGS= -std=c++17 -O2 -I. `pkg-config acidcam opencv4 --cflags`
LDFLAGS= `pkg-config acidcam opencv4 --libs`

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
