CXX_FLAGS=-std=c++1z
LDFLAGS=
CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix ,$(notdir $(CPP_FILES:.cpp=.o)))
OUTPUT_NAME=sym-test

%.o: %.cpp tree.hpp table.hpp
	$(CXX) $(CXX_FLAGS) -c -o $@ $<
  
all: $(OBJ_FILES)
	$(CXX) $(OBJ_FILES) -o $(OUTPUT_NAME)  $(LDFLAGS)

install: all
	cp $(OUTPUT_NAME) /usr/local/bin

clean:
	rm -f $(OUTPUT_NAME) *.o 

