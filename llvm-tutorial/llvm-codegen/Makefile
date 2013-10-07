
all: codegen

%: %.cpp
	clang++ -Wall -std=c++11 -g $< `llvm-config --cxxflags --ldflags --libs core jit native` -o $@

