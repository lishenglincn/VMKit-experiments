// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
//===------- RJITCompiler.h - The Reactor just in time compiler -----------===//
//
//                            The VMKit project
//
// This file is distributed under the Purdue University Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _RJITCOMPILER_H_
#define _RJITCOMPILER_H_

#include "llvm/CodeGen/GCMetadata.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/ExecutionEngine/JITEventListener.h"
#include "llvm/GVMaterializer.h"
#include "ToyCompiler.h"
#include "ToyIntrinsics.h"

namespace Toy {

class ToyJITCompiler;

/*
 * class ToyJITListener :
 * 	Voir question "Transmission des stack maps"
 */
class ToyJITListener : public llvm::JITEventListener {
  ToyJITCompiler* TheCompiler;
public:
  ToyJITListener(ToyJITCompiler* Compiler) {
    TheCompiler = Compiler;
  }

  virtual void NotifyFunctionEmitted(
      const llvm::Function &F,
      void *Code,
      size_t Size,
      const llvm::JITEventListener::EmittedFunctionDetails &Details);
};



/*
 * Compléter l'héritage de la classe ToyJITCompiler
 * Note : les méthodes virtuelles pures héritées sont implémentées dans ToyJITCompiler.cc
 */
class ToyJITCompiler : public ToyCompiler /*, ? */ {
	public:

		ToyJITListener listener;
		llvm::ExecutionEngine* ee;

		ToyJITCompiler();
		~ToyJITCompiler();  

		/*
		 * Question 4.1
		 * A compléter
		 */

		static ToyJITCompiler* create();
		void* jitCompile();
};
 
} // end namespace R

#endif
