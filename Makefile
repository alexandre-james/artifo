CC = g++

CPP_FILES = src/image/*.cpp

OBJ_FILES = $(CPP_FILES:.cu=.o)

CXX_FLAGS = -Wall -O3
LDXX_FLAGS =

all: build

build: $(CPP_FILES)
	$(CC) src/main.cpp -o tifo $(CPP_FILES) $(CXX_FLAGS) $(LDXX_FLAGS)

.PHONY: all clean build

clean:
	rm -f tifo $(OBJ_FILES)