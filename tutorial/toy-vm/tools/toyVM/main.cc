// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
//===------------ main.cpp - Simple execution of Reactor ----------------===//
//
//                          The VMKit project
//
// This file is distributed under the Purdue University Open Source
// License. See LICENSE.TXT for details.
//
//===--------------------------------------------------------------------===//

#include "ToyVM.h"
#include "ToyJITCompiler.h"
#include "vmkit/JIT.h"

using namespace Toy;

extern vmkit::CompiledFrames* frametables[];

int main(int argc, char **argv)
{
	// Initialize base components.
	vmkit::VmkitModule::initialise(argc, argv);
	vmkit::Collector::initialise(argc, argv);

	// Create the allocator that will allocate the bootstrap loader and the JVM.
	vmkit::BumpPtrAllocator Allocator;
	ToyJITCompiler* Comp = ToyJITCompiler::create();

	ToyVM * vm = new(Allocator, "ToyVM") ToyVM(Allocator, Comp, frametables);
	vm->runApplication(argc, argv);
	vm->waitForExit();

	vmkit::System::Exit(0);

	return 0;
}
