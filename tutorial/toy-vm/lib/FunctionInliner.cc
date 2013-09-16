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

using namespace llvm;

namespace Toy {

  class FunctionInliner : public FunctionPass {
  public:
    static char ID;

		ToyCompiler* compiler;
		llvm::SmallPtrSet<const Function*, 16> NeverInline;
		llvm::InlineCostAnalysis CA;
		unsigned int inlineThreshold;

		FunctionInliner() : FunctionPass(ID){}
    FunctionInliner(ToyCompiler* compiler, unsigned int th=225) : FunctionPass(ID) { this->compiler = compiler; inlineThreshold = th; }

    virtual const char* getPassName() const {
      return "incrementally inline functions";
    }

		InlineCost getInlineCost(CallSite CS) {
			return CA.getInlineCost(CS, inlineThreshold);
		}

    virtual bool runOnFunction(Function &F);
  private:
  };

  char FunctionInliner::ID = 0;
  RegisterPass<FunctionInliner> X("FunctionInliner",
  															"Inlining Pass that inlines evaluator's functions.");

	bool FunctionInliner::runOnFunction(Function& F) {
		bool Changed = false;
		const DataLayout *TD = getAnalysisIfAvailable<DataLayout>();
		for (Function::iterator BI = F.begin(), BE = F.end(); BI != BE; BI++) { 
			BasicBlock *Cur = BI; 

			for (BasicBlock::iterator II = Cur->begin(), IE = Cur->end(); II != IE;) {
				Instruction *I = II++;
				if (I->getOpcode() != Instruction::Call &&
						I->getOpcode() != Instruction::Invoke) {
					continue;
				}
				CallSite Call(I);
				Function* Temp = Call.getCalledFunction();

				if(!Temp){
					continue;
				}

				if(Temp->getParent() == compiler->selfModule) {
					Temp->Materialize();
				}

				if(!Temp->isDeclaration()) {
					llvm::InlineCost cost = getInlineCost(Call);
					if(cost.isAlways() || (!cost.isNever() && cost.getCost() < inlineThreshold)) {
//						jitprintf("*** Inline %s into %s [%d] ***\n", Temp->getName().data(), F.getName().data(), cost.isAlways()? -1 : cost.getValue());
						llvm::InlineFunctionInfo IFI(NULL, TD);
						Changed |= llvm::InlineFunction(Call, IFI, false);
//						jitprintf("*** Inline Done ***\n");
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

	FunctionPass* createFunctionInlinerPass(ToyCompiler* compiler) {
		return new FunctionInliner(compiler);
	}

}
