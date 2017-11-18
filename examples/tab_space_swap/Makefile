CXX=g++
CXX_FLAGS= -std=c++1z

CPP_FILES := $(wildcard *.cpp)
EXE_FILES := $(addprefix ,$(notdir $(CPP_FILES:.cpp=.prog)))

%.prog: %.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $<

all: $(EXE_FILES)


install: all
	cp tabs2space.prog /usr/local/bin

clean:
	rm -f *.prog
