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
using namespace vmkit;

extern CompiledFrames* frametables[];

int main(int argc, char **argv){
  // Initialize base components.
  VmkitModule::initialise(argc, argv);
  Collector::initialise(argc, argv);

  // Create the allocator that will allocate the bootstrap loader and the JVM.
  vmkit::BumpPtrAllocator Allocator;
  ToyJITCompiler* Comp = ToyJITCompiler::create();

/*
 * A completer
 */

  System::Exit(0);

  return 0;
}
