

CXX_FLAGS=-std=c++17 -O2
SDL_CXXFLAGS= `sdl2-config --cflags`
SDL_LDFLAGS= `sdl2-config --libs`
CPP_FILES := $(wildcard *.cpp)
OBJ_FILES := $(addprefix ,$(notdir $(CPP_FILES:.cpp=.o)))
OUTPUT_NAME=test-game

%.o: %.cpp
	$(CXX) $(CXX_FLAGS) $(SDL_CXXFLAGS) -c -o $@ $<
  
all: $(OBJ_FILES) 
	$(CXX) $(OBJ_FILES)  -o $(OUTPUT_NAME)  $(LDFLAGS) $(SDL_LDFLAGS)

install: all
	cp $(OUTPUT_NAME) /usr/local/bin

clean:
	rm -f $(OUTPUT_NAME) *.o 