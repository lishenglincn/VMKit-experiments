#include "vm/core/Thread.h"
#include "vm/core/VM.h"

using namespace vm::core;

Thread::Thread(VM & vm)
	: vmkit::MutatorThread()
{
	this->MyVM = &vm;
}

