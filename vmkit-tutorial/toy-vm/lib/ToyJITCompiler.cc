// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
//===------- RJITCompiler.cpp - The Reactor just in time compiler -----------===//
//
//                            The VMKit project
//
// This file is distributed under the Purdue University Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#include "llvm/IR/Constants.h"
#include "llvm/IR/DerivedTypes.h"
#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/LLVMContext.h"
#include "llvm/IR/Module.h"
#include "llvm/DebugInfo.h"
#include "llvm/CodeGen/GCStrategy.h"
#include "llvm/CodeGen/JITCodeEmitter.h"
#include "llvm/CodeGen/MachineFunction.h"
#include "llvm/ExecutionEngine/ExecutionEngine.h"
#include "llvm/Support/CommandLine.h"
#include "llvm/Support/ManagedStatic.h"
#include "llvm/Support/Debug.h"
#include "llvm/Support/raw_ostream.h"
#include "llvm/IR/DataLayout.h"
#include <llvm/LinkAllPasses.h>

#include "VmkitGC.h"
#include "vmkit/VirtualMachine.h"
#include "vmkit/JIT.h"
#include "ToyVM.h"
#include "ToyThread.h"

#include "ToyJITCompiler.h"

using namespace Toy;


void ToyJITListener::NotifyFunctionEmitted(const llvm::Function & F, void * Code, size_t Size, const EmittedFunctionDetails & Details)
{
	Assert(F.hasGC());
	fprintf(stderr, "function emitted\n");
	/* Question 4.5
	 * A Compléter
	 */
}


ToyJITCompiler::ToyJITCompiler()
	: ToyCompiler()
	, listener(this)
{
	fprintf(stderr, "ToyJITCompiler::ToyJITCompiler()\n");

		std::string err;
		llvm::EngineBuilder engine (selfModule);
		llvm::TargetOptions options;
		options.NoFramePointerElim = true;
		engine.setTargetOptions(options);
		engine.setEngineKind(llvm::EngineKind::JIT);
		engine.setErrorStr(&err);


	/*
	 * Question : "Initialisation du cœur du compilateur JIT"
	 *
	 * A completer
	 *
	 * Instancier l'executionEngine (ee) et decommenter le code
	 */
		
		ee = engine.create();

		ee->RegisterJITEventListener(&listener);
		ee->DisableLazyCompilation(0);
		ee->addModule(selfModule);
		selfModule->setDataLayout(ee->getDataLayout()->getStringRepresentation());
		selfModule->setMaterializer(this);
		selfModule->setTargetTriple(vmkit::VmkitModule::getHostTriple());

	/*
	 * A completer
	 * Le code suivant parcours tout le module en itérant sur les déclarations (fonctions + variables globales).
	 * Il ne reste plus qu'a faire le mapping dans l'executionEngine entre la déclaration l'IR et l'adresse du
	 * symbol correspondant.
	 *
	 */
		for(llvm::Module::iterator cur=selfModule->begin(), end=selfModule->end(); cur!=end; cur++) {
			void* ptr = dlsym(RTLD_DEFAULT, cur->getName().data());
			if(ptr){
				// Faire le mapping ici
			}
		}
		for(llvm::Module::global_iterator cur=selfModule->global_begin(), end=selfModule->global_end(); cur!=end; cur++) {
			void* ptr = dlsym(RTLD_DEFAULT, cur->getName().data());
			if(ptr){
				// Faire le mapping ici
			}
		}
}



/*
 * Question 4.1
 * Inherited methods from ?
 */
bool ToyJITCompiler::MaterializeModule(llvm::Module *M, std::string *ErrInfo) {
	nyi();
	abort();
	return false;
}

bool ToyJITCompiler::isDematerializable(const llvm::GlobalValue *GV) const {
	return 0;
}

bool ToyJITCompiler::Materialize(llvm::GlobalValue *GV, std::string *ErrInfo) {
	llvm::Function* F = llvm::dyn_cast<llvm::Function>(GV);

	if(!F || !F->isMaterializable())
		return false;

	generateCode(F);
	return false;
}

bool ToyJITCompiler::isMaterializable(const llvm::GlobalValue *GV) const {
	const llvm::Function *F = llvm::dyn_cast<const llvm::Function>(GV);
	return F && F->isDeclaration() && !strncmp(GV->getName().data(), "toy-function", 12);
}
/*****************************************************************************/



ToyJITCompiler::~ToyJITCompiler() {
	// ee n'est pas encore défini
	ee->removeModule(selfModule);
	delete ee;
}



ToyJITCompiler* ToyJITCompiler::create() {
	return new ToyJITCompiler();
}



void* ToyJITCompiler::jitCompile()
{
	vmkit::VmkitModule::protectIR();

	llvm::Function* func = llvmFunction();

	// Call generateCode method
	func->Materialize();

	/*
	 * Question 4.3
	 * Obtenir le pointeur vers du code natif à l'aide de l'executionEngine et
	 * de la fonction LLVM func.
	 *
	 */
	void* res = NULL;

	if (!func->isDeclaration()) {
		/*
		 * Question 4.5
		 * Ici ToyJITCompiler transmet les informations GC à VMKit
		 * à l'aide d'un appel à vmkit::VmkitModule::addToVM
		 *
		 */
	}
	vmkit::VmkitModule::unprotectIR();
	return res;
}


//void ToyJITCompiler::initPassManager() {
//	** Initialisation à compléter **
//
//	pm->add(llvm::createBasicAliasAnalysisPass());
//
//	pm->add(createFunctionInlinerPass(this));
//
//	pm->add(llvm::createCFGSimplificationPass());      // Clean up disgusting code
//	pm->add(llvm::createPromoteMemoryToRegisterPass());// Kill useless allocas
//	pm->add(llvm::createInstructionCombiningPass()); // Cleanup for scalarrepl.
//	pm->add(llvm::createScalarReplAggregatesPass()); // Break up aggregate allocas
//	pm->add(llvm::createInstructionCombiningPass()); // Cleanup for scalarrepl.
//	pm->add(llvm::createJumpThreadingPass());        // Thread jumps.
//	pm->add(llvm::createCFGSimplificationPass());    // Merge & remove BBs
//	pm->add(llvm::createInstructionCombiningPass()); // Combine silly seq's
//	pm->add(llvm::createCFGSimplificationPass());    // Merge & remove BBs
//
//	pm->add(llvm::createReassociatePass());          // Reassociate expressions
//	pm->add(llvm::createLoopRotatePass());           // Rotate loops.
//	pm->add(llvm::createLICMPass());                 // Hoist loop invariants
//	pm->add(llvm::createLoopUnswitchPass());         // Unswitch loops.
//	pm->add(llvm::createInstructionCombiningPass());
//	pm->add(llvm::createIndVarSimplifyPass());       // Canonicalize indvars
//	pm->add(llvm::createLoopDeletionPass());         // Delete dead loops
//	pm->add(llvm::createLoopUnrollPass());           // Unroll small loops*/
//	pm->add(llvm::createInstructionCombiningPass()); // Clean up after the unroller
//	pm->add(llvm::createGVNPass());                  // Remove redundancies
//	pm->add(llvm::createMemCpyOptPass());            // Remove memcpy / form memset
//	pm->add(llvm::createSCCPPass());                 // Constant prop with SCCP
//
//	// Run instcombine after redundancy elimination to exploit opportunities
//	// opened up by them.
//	pm->add(llvm::createInstructionCombiningPass());
//	pm->add(llvm::createJumpThreadingPass());         // Thread jumps
//	pm->add(llvm::createDeadStoreEliminationPass());  // Delete dead stores
//	pm->add(llvm::createAggressiveDCEPass());         // Delete dead instructions
//	pm->add(llvm::createCFGSimplificationPass());     // Merge & remove BBs
//
//	** Initialisation des passes d'optimisation **
//}
