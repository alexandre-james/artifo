CC = g++

CU = nvcc

CPP_FILES = src/image/*.cpp src/features/*.cpp src/modifier/*.cpp src/tools/*.cpp src/filter/*.cpp

CU_FILES = src/image/*.cpp src/features/*.cpp src/modifier/*.cu src/tools/*.cpp src/filter/*.cpp
CU_FILES += src/modifier/filter.cpp src/modifier/mask.cpp src/modifier/modifier.cpp src/modifier/structure.cpp

OBJ_FILES = $(CPP_FILES:.cpp=.o)

CXX_FLAGS = -Wall -O3 -std=c++17 -g
CXX_FLAGS += -m64 -march=native
CXX_FLAGS += # -fopt-info-vec-optimized -fopt-info-vec-missed -ftree-vectorize
LDXX_FLAGS =

CU_FLAGS = -O3 -g -G

all: build

build: $(CPP_FILES)
	$(CC) src/main.cpp -o tifo $(CPP_FILES) $(CXX_FLAGS) $(LDXX_FLAGS)

cuda: $(CU_FILES) 
	$(CU) src/main.cpp -o tifo $(CU_FILES) $(CU_FLAGS)

.PHONY: all clean build

clean:
	rm -f tifo $(OBJ_FILES) output/*.png