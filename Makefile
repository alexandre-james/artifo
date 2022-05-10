CC = g++

CPP_FILES = src/image/*.cpp src/features/*.cpp src/modifier/*.cpp

OBJ_FILES = $(CPP_FILES:.cpp=.o)

CXX_FLAGS = -Wall -O3 -std=c++17
LDXX_FLAGS =

all: build

build: $(CPP_FILES)
	$(CC) src/main.cpp -o tifo $(CPP_FILES) $(CXX_FLAGS) $(LDXX_FLAGS)

.PHONY: all clean build

clean:
	rm -f tifo $(OBJ_FILES)