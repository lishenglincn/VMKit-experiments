#include <cstdio>
#include "vm/core/VM.h"
#include "vm/core/Thread.h"

using namespace vm::core;

VM::VM(vmkit::BumpPtrAllocator & alloc, vmkit::CompiledFrames ** frames)
	: VirtualMachine(alloc, frames)
{
}

void VM::traceObject(gc * object, word_t closure)
{
}

void * VM::getType(gc * header)
{
	return nullptr;
}

void VM::setType(gc * header, void * type)
{
}

size_t VM::getObjectSize(gc * object)
{
	return 0;
}

void VM::printMethod(vmkit::FrameInfo * fi, word_t ip, word_t addr)
{
}

void VM::nullPointerException()
{
}

void VM::stackOverflowError()
{
}

void VM::runApplication(int argc, char ** argv)
{
	auto * thread = new Thread(*this);
	this->mainThread = thread;
	thread->start(mainStart);
}

void VM::mainStart(vmkit::Thread * const _thread)
{
	auto & thread = *static_cast<Thread *>(_thread);
	fprintf(stderr, "Thread assigned: id = %lx\n", thread.getThreadID());
	thread.MyVM->exit();
}

