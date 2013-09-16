// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
//===--------- ToyVM.cc - Toy virtual machine description --------------===//
//
//                          The VMKit project
//
// This file is distributed under the Purdue University Open Source
// License. See LICENSE.TXT for details.
//
//===------------------------------------------------------------------===//

//===------------------ Header Includes ------------------===//

#include "ToyVM.h"
#include "ToyThread.h"
#include "ToyCompiler.h"
#include "ToyJITCompiler.h"
#include <sys/time.h>
#include <iostream>

//===------------------ End Header Includes -------------===//

using namespace Toy;

void ClArgumentsInfo::readArgs(ToyVM *vm) {
  int dashdash = 0;
	chronometer = 0;
	verbose = 0;
	jit=false;

  for(int i = 1; i < argc; i++){
    char *current = argv[i];
    if(current[0] == '-' && !dashdash){
      if(!strcmp(current, "-v") || !strcmp(current, "--verbose"))
        verbose ++;
      else if(!strcmp(current, "-time"))
				chronometer = 1;
      else if(!strcmp(current, "-jit"))
				jit = true;
      else if(!strcmp(current, "--"))
        dashdash ++;
      else if(!strcmp(current, "--version")){
				printVersion();
				exit(0);
			} else {
        warning("Unknown option: %s\n", current);
      }
    } else {

    }
  }
}

void ClArgumentsInfo::printInformation() {
  fprintf(stderr, "Syntax: toyVM [ -v|--verbose ] [ -time ]  [ xMin=-2 xMax=1 yMin=-1 yMax=1 width=800 height=600 ]\n");
}

void ClArgumentsInfo::printVersion() {
  fprintf(stdout, "ToyVM for VMKit tutorial version 0.1\n");
}


//ToyVM::ToyVM(vmkit::BumpPtrAllocator& Alloc, ToyCompiler* compiler, vmkit::CompiledFrames** frames) :
//	VirtualMachine(Alloc, frames) {
//	this->compiler = compiler;
//	compiler->vm = this;
//}

//size_t ToyVM::getObjectSize(gc* obj) {
//	nyi();
//  return 0;
//}

//void ToyVM::printMethod(vmkit::FrameInfo* FI, word_t ip, word_t addr) {
//	if (FI->Metadata == NULL) {
//		vmkit::MethodInfoHelper::print(ip, addr);
//		return;
//	}
//}

//void ToyVM::runApplication(int argc, char** argv) {
//  argumentsInfo.argc = argc;
//  argumentsInfo.argv = argv;
//  /*
//   * A completer
//   * Question 2.2
//   */
//}




//void ToyVM::mainStart(ToyThread* thread) {
//	printf("Starting ToyVM\n");
//
//  ToyVM* vm = thread->vm();
//
//  vm->argumentsInfo.readArgs(vm);
//
//	if(vm->argumentsInfo.chronometer) {
//		// Start timer
//		printf("Starting timer\n");
//		gettimeofday(&(vm->tbegin), NULL);
//	}

	/*
	 * A Compléter Question 2.3 'execute'
	 */

//	if(vm->argumentsInfo.chronometer) {
//		// End timer
//		gettimeofday(&(vm->tend), NULL);
//		printf("Timer stopped\n");
//		// Compute execution time
//		vm->texec = ((double) (1000 * (vm->tend.tv_sec - vm->tbegin.tv_sec) + ((vm->tend.tv_usec - vm->tbegin.tv_usec) / 1000))) / 1000.;
//		std::cout << "Execution time : " << vm->texec << " s" << std::endl;
//	}

//	printf("Closing ToyVM\n");
	/*
	 * A completer
	 * Question 2.2
	 */
//}
