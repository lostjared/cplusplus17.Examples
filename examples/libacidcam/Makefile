OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
PROGRAM=libacidcam-test
CFLAGS= -std=c++17 `pkg-config opencv4 acidcam --cflags`
LDFLAGS= `pkg-config opencv4 acidcam --libs`

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

$(PROGRAM): $(OBJ)
	$(CXX) -o $(PROGRAM) $(OBJ) $(LDFLAGS)

all: example

.PHONY: clean
clean:
	rm -f $(PROGRAM) *.o
