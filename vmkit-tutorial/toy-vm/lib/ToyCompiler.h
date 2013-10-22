// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
//===------- RLLVMCompiler.h - The Reactor just in time compiler -----------===//
//
//                            The VMKit project
//
// This file is distributed under the Purdue University Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _RLLVMCOMPILER_H_
#define _RLLVMCOMPILER_H_

#include "llvm/Pass.h"
#include "llvm/IR/Function.h"
#include "llvm/PassManager.h"
#include "llvm/ADT/DenseMap.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"

#include <map>

#include "vmkit/Allocator.h"
#include "ToyIntrinsics.h"

extern "C" const char toyvm_module_path[];

namespace llvm {
  class BasicBlock;
  class DIBuilder;
}

namespace Toy {
	class ToyVM;

  class ToyCompiler {
  		static llvm::Module* loadSelfModule();

  	protected:
		ToyIntrinsics Intrinsics;

  	public:
		ToyVM*                   	 vm;
		llvm::Module*              selfModule;


		ToyCompiler();
		virtual ~ToyCompiler();

		ToyIntrinsics* getIntrinsics() { return &Intrinsics; }

		llvm::Function* llvmFunction();

		void generateCode(llvm::Function* func);

  };
		extern llvm::FunctionPass* createFunctionInlinerPass(ToyCompiler* compiler);
} // end namespace R

#endif
