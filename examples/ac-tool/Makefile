OBJ=$(patsubst %.cpp,%.o,$(wildcard *.cpp))

CFLAGS= -std=c++17 -O2 `pkg-config opencv4 acidcam --cflags`
LDFLAGS= `pkg-config opencv4 acidcam --libs`

%.o: %.cpp
	$(CXX) $(CFLAGS) $< -c -o $@

per.test: $(OBJ)
	$(CXX) -o ac-tool $(OBJ) $(LDFLAGS)

all: example

install:
	cp ac-tool /usr/local/bin

.PHONY: clean
clean:
	rm -f ac-tool *.o
