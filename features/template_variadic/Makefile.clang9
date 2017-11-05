CXX=g++
CXX_FLAGS= -std=c++1z

CPP_FILES := $(wildcard *.cpp)
EXE_FILES := $(addprefix ,$(notdir $(CPP_FILES:.cpp=.prog)))

%.prog: %.cpp
	$(CXX) $(CXX_FLAGS) -o $@ $<

all: $(EXE_FILES)

clean:
	rm -f *.prog
