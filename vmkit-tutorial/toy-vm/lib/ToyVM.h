// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
//===--------- Reactor.h - R virtual machine description --------------===//
//
//                          The VMKit project
//
// This file is distributed under the Purdue University Open Source
// License. See LICENSE.TXT for details.
//
//===------------------------------------------------------------------===//

#ifndef _REACTOR_H_
#define _REACTOR_H_

//===------------------ Header Includes ------------------===//

#include <llvm/GVMaterializer.h>

#include <cstring>
#include "util.h"
#include "vmkit/MethodInfo.h"
#include "vmkit/VirtualMachine.h"

//===------------------ End Header Includes -------------===//

namespace Toy {
	class ToyCompiler;
	class RModule;
	class ToyVM;
	class Environment;
	class ToyThread;

	/// ClArgumentsInfo - used for argument passing.
	///
	class ClArgumentsInfo {
	public:
		int argc; // Application Arguments count
		char** argv; // Application Arguments
		int verbose; // Verbose mode level
		int chronometer; // compute execution time
		bool jit; // use jit

		void readArgs(ToyVM *vm);

		static void printInformation();
		static void printVersion();
	};




	/// ToyVM - A minimal Virtual Machine.
	///
	class ToyVM : public vmkit::VirtualMachine {
	private:
		// Profiling vars
		struct timeval tbegin,tend;
		double texec;
		// end profiling vars

	public:
		/// argumentsInfo - The command line arguments given to the vm
		///
		ClArgumentsInfo argumentsInfo;

		/// compile - The JIT compiler
		ToyCompiler* compiler;

		/// ToyVM - Allocates a new Toy Virtual Machine.
		ToyVM(vmkit::BumpPtrAllocator& Alloc, ToyCompiler* compiler, vmkit::CompiledFrames** frames);

	public:
		virtual size_t getObjectSize(gc* obj) override;
		virtual void printMethod(vmkit::FrameInfo* FI, word_t ip, word_t addr) override;
		virtual void runApplication(int argc, char** argv) override;
		virtual void nullPointerException() override;
		virtual void stackOverflowError() override;
		virtual void traceObject(gc* object, word_t closure) override;
		virtual void setType(gc* header, void* type) override;
		virtual void* getType(gc* header) override;

		virtual void startCollection() override;
		virtual void endCollection() override;

	private:
		static void mainStart(ToyThread* thread);
	};

} // end namespace R

#endif // protect from multiple inclusion 
