
SrcList := main vm/core/VM vm/core/Thread vm/core/Root

BuildMode := Release

LLVMConfig := /home/mishun/cs/llvm-3.3/$(BuildMode)/bin/llvm-config
VMKitPath := /home/mishun/cs/vmkit-svn

CXXFLAGS := -O2 -Wall -MMD -emit-llvm \
	`$(LLVMConfig) --cxxflags` \
	-I$(VMKitPath)/include \
	-I$(VMKitPath)/lib/vmkit/MMTk \
	-I$(CURDIR)/src

LIBS := `$(LLVMConfig) --ldflags` \
	$(patsubst %,$(VMKitPath)/$(BuildMode)/lib/lib%.a, FinalMMTk J3 Classpath Vmkit VmkitCompiler CommonThread FinalMMTk) \
	-lz `$(LLVMConfig) --libs jit nativecodegen scalaropts instrumentation ipa ipo core bitreader`

all: $(BuildMode)/bin/main

vpath %.cpp src

.SECONDARY:
$(BuildMode)/obj/%.bc: %.cpp
	mkdir -p $(dir $@)
	clang++ $(CXXFLAGS) -c $< -o $@

$(BuildMode)/bin/%.bc: $(patsubst %,$(BuildMode)/obj/%.bc, $(SrcList))
	mkdir -p $(dir $@)
	llvm-link -o $@ $^

$(BuildMode)/bin/%: $(BuildMode)/bin/%.bc
	clang++ -o $@ $^ $(LIBS)

-include $(patsubst %,$(BuildMode)/obj/%.d,$(SrcList))
