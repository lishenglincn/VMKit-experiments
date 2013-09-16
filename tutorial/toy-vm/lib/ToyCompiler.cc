// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
//===------- RLLVMCompiler.cpp - The Reactor just in time compiler ---------===//
//
//                            The VMKit project
//
// This file is distributed under the Purdue University Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/DerivedTypes.h>

#include <llvm/ADT/OwningPtr.h>

#include <llvm/Support/MemoryBuffer.h>
#include <llvm/Support/system_error.h>
#include <llvm/Support/TargetSelect.h>
#include <llvm/IR/IRBuilder.h>

#include <llvm/Bitcode/ReaderWriter.h>

#include <llvm/Analysis/Verifier.h>
#include <llvm/DIBuilder.h>
#include <llvm/IR/DataLayout.h>

#include "util.h"
#include "ToyVM.h"
#include "ToyCompiler.h"

using namespace Toy;
using namespace llvm;

ToyCompiler::ToyCompiler() {
	selfModule = loadSelfModule();
	if(selfModule)
		Intrinsics.init(selfModule);
}

ToyCompiler::~ToyCompiler() {}

llvm::Module* ToyCompiler::loadSelfModule() {
	llvm::InitializeNativeTarget();

	llvm::OwningPtr<llvm::MemoryBuffer> buf;
	llvm::error_code err;

	/*
	 * Question 4.2
	 *
	 * Charger l'IR du module toyVM à l'aide de la varialbe 'toyvm_module_path'
	 * Retourner le module ainsi chargé.
	 *
	 */

	//	if((err = llvm::MemoryBuffer::getFile( ? , buf))) {
	//		warning("unable to open my own bitcode %s", err.message().c_str());
	//	}
	//
	//	return llvm::ParseBitcodeFile(buf.take(), llvm::getGlobalContext());
	return NULL;
}



/*
 * Le compilateur étant minimal, il ne génère qu'une seule fonction et prend en
 * paramètre cette derniere. Il sagit simplement de faire l'appel à la fonction
 * jitCompute de la toyVM pour lancer le calcul de la fractale de Mandelbrot.
 *
 */
void ToyCompiler::generateCode(llvm::Function* func) {
	llvm::Function* func_to_call = NULL;

	/*
	 * Question 4.2
	 * Générer dans func un appel à la fonction jitCompute.
	 */

	Assert(func_to_call, "jit function not found !");

	llvm::BasicBlock* bb = llvm::BasicBlock::Create(func->getContext(), "entry", func);
	llvm::Function::arg_iterator args = func->arg_begin();
	llvm::IRBuilder<> builder(bb);
	llvm::Value* ret = builder.CreateCall(func_to_call, args);
	builder.CreateRet(ret);

	// Verify basic block consistency
	error_on(llvm::verifyFunction(*func, llvm::PrintMessageAction),
			"Error on verification. Bad function generation on jit for \"%s\"", func->getName().data());

	/*
	 * Question 4.4
	 * optimiser le code JIT à l'aide du FPM
	 *
	 */
}


/*
 * Les Intrinsics dans toyVM sont uniquement des raccourcis vers les types llvm.
 *
 * Dans la méthode llvmFunction(), on créé une déclaration de fonction dont le
 * prototype est Intrinsics.toyFunctionType (voir la définition dans Intrinsics)
 * et dont le nom est 'toy-function'. Cette déclaration est insérée dans le module
 * contenant l'IR de la toyVM.
 *
 * Note : Il est important d'affecter "vmkit" en tant que GC de la fonction
 * pour générer correctement les informations de GC.
 */
llvm::Function* ToyCompiler::llvmFunction() {
	llvm::Function* func = Function::Create(Intrinsics.toyFunctionType,
			GlobalValue::ExternalLinkage, "toy-function", selfModule);
	func->setGC("vmkit");
	return func;
}
