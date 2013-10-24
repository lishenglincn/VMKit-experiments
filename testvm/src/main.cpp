#include <vmkit/JIT.h>
#include <vmkit/Allocator.h>
#include <VmkitGC.h>
#include "vm/core/VM.h"

int main(int argc, char ** argv)
{
	vmkit::VmkitModule::initialise(argc, argv);
	vmkit::Collector::initialise(argc, argv);

	vmkit::BumpPtrAllocator allocator;

	auto * vm = new(allocator, "VM") vm::core::VM(allocator, nullptr);
	vm->runApplication(argc, argv);
	vm->waitForExit();

	return 0;
}

