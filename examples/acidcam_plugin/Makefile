CXX_FLAGS=-std=c++17 `pkg-config opencv4 --cflags`
LDFLAGS= `pkg-config opencv4 --libs`
CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix ,$(notdir $(CPP_FILES:.cpp=.o)))
OUTPUT_NAME=filter

%.o: %.cpp 
	$(CXX) $(CXX_FLAGS) -c -o $@ $<
  
all: $(OBJ_FILES) 
	$(CXX) -shared $(OBJ_FILES)  -o $(OUTPUT_NAME)  $(LDFLAGS)

clean:
	rm -f $(OUTPUT_NAME) *.o 

