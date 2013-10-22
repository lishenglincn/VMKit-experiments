#include "ToyCompiler.h"

#include "llvm/IR/Function.h"
#include "llvm/IR/Instructions.h"
#include "llvm/IR/Module.h"
#include "llvm/Pass.h"
#include "llvm/Support/CallSite.h"
#include "llvm/IR/DataLayout.h"
#include "llvm/Analysis/InlineCost.h"
#include "llvm/ADT/SmallPtrSet.h"
#include "llvm/Transforms/Utils/Cloning.h"


namespace Toy {

	class FunctionInliner : public llvm::FunctionPass {
	public:
		static char ID;

		ToyCompiler* compiler;
		llvm::SmallPtrSet<const llvm::Function *, 16> NeverInline;
		llvm::InlineCostAnalysis CA;
		unsigned int inlineThreshold;

		FunctionInliner() : FunctionPass(ID) {}
		FunctionInliner(ToyCompiler* compiler, unsigned int th=225) : FunctionPass(ID) { this->compiler = compiler; inlineThreshold = th; }

		virtual const char* getPassName() const {
			return "incrementally inline functions";
		}

		llvm::InlineCost getInlineCost(llvm::CallSite CS) {
			return CA.getInlineCost(CS, inlineThreshold);
		}

		virtual bool runOnFunction(llvm::Function &F);
	private:
	};

	char FunctionInliner::ID = 0;
	llvm::RegisterPass<FunctionInliner> X("FunctionInliner", "Inlining Pass that inlines evaluator's functions.");

	bool FunctionInliner::runOnFunction(llvm::Function & F) {
		bool Changed = false;
		const llvm::DataLayout *TD = getAnalysisIfAvailable<llvm::DataLayout>();
		for (llvm::Function::iterator BI = F.begin(), BE = F.end(); BI != BE; BI++) { 
			llvm::BasicBlock *Cur = BI; 

			for (llvm::BasicBlock::iterator II = Cur->begin(), IE = Cur->end(); II != IE;) {
				llvm::Instruction *I = II++;
				if (I->getOpcode() != llvm::Instruction::Call &&
						I->getOpcode() != llvm::Instruction::Invoke) {
					continue;
				}
				llvm::CallSite Call(I);
				llvm::Function* Temp = Call.getCalledFunction();

				if(!Temp){
					continue;
				}

				if(Temp->getParent() == compiler->selfModule) {
					Temp->Materialize();
				}

				if(!Temp->isDeclaration()) {
					llvm::InlineCost cost = getInlineCost(Call);
					if(cost.isAlways() || (!cost.isNever() && cost.getCost() < inlineThreshold)) {
						printf("*** Inline %s into %s [%d] ***\n", Temp->getName().data(), F.getName().data(), cost.isAlways()? -1 : cost.getCost());
						llvm::InlineFunctionInfo IFI(NULL, TD);
						Changed |= llvm::InlineFunction(Call, IFI, false);
						printf("*** Inline Done ***\n");
						if(Changed){
							II = Cur->begin();
							continue;
						}
					}
				}
      }
    }
//		F.viewCFGOnly();exit(1);
		return Changed;
	}

	llvm::FunctionPass* createFunctionInlinerPass(ToyCompiler* compiler) {
		return new FunctionInliner(compiler);
	}

}
