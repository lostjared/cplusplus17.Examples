OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))
PROGRAM=img_convert
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
install:
	cp $(PROGRAM) /usr/local/bin
