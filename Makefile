CC = g++

CU = nvcc

CPP_FILES = src/image/*.cpp src/features/*.cpp src/modifier/*.cpp src/tools/*.cpp src/filter/*.cpp src/construct/*.cpp

CU_FILES = src/image/*.cpp src/features/*.cpp src/modifier/*.cu src/tools/*.cpp src/filter/*.cpp src/construct/*.cpp
CU_FILES += src/modifier/filter.cpp src/modifier/modifier.cpp src/modifier/transformation.cpp

OBJ_FILES = $(CPP_FILES:.cpp=.o)

CXX_FLAGS = -Wall -O3 -std=c++17
CXX_FLAGS += -m64 -march=native
CXX_FLAGS +=# -fopt-info-vec-optimized -fopt-info-vec-missed -ftree-vectorize

CU_FLAGS = -O3

D_FLAGS = -g
CUD_FLAGS = -G

BASE = src/main.cpp -o artifo

all: build

build: $(CPP_FILES)
	$(CC) $(BASE) $(CPP_FILES) $(CXX_FLAGS)

debug: $(CPP_FILES)
	$(CC) $(BASE) $(CPP_FILES) $(CXX_FLAGS) $(D_FLAGS)

cuda: $(CU_FILES) 
	$(CU) $(BASE) $(CU_FILES) $(CU_FLAGS)

cuda_debug: $(CU_FILES)
	$(CU) $(BASE) $(CU_FILES) $(CU_FLAGS) $(D_FLAGS) $(CUD_FLAGS)

.PHONY: all clean build

clean:
	rm -f artifo $(OBJ_FILES) output/*.png output/*.gif