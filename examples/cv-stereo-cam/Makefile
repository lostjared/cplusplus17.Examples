OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
PROGRAM=cv-stereo-cam
CFLAGS= -std=c++17 `pkg-config opencv4 --cflags`
LDFLAGS=`pkg-config opencv4 --libs`

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

$(PROGRAM): $(OBJ)
	$(CXX) -o $(PROGRAM) $(OBJ) $(LDFLAGS)

all: $(PROGRAM)

.PHONY: clean
clean:
	rm -f $(PROGRAM) *.o
