CC = g++

CPP_FILES = 

OBJ_FILES = $(CPP_FILES:.cu=.o)

CXX_FLAGS = -Wall -Wextra -O3
LDXX_FLAGS =

all: build

build: $(CPP_FILES)
	$(CC) src/main.cpp -o tifo $(CPP_FILES) $(CXX_FLAGS) $(LDXX_FLAGS)

.PHONY: all clean build

clean:
	rm -f tifo $(OBJ_FILES)