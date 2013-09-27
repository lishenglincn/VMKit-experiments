#include <llvm/DerivedTypes.h>
#include <llvm/ExecutionEngine/ExecutionEngine.h>
#include <llvm/ExecutionEngine/JIT.h>
#include <llvm/IRBuilder.h>
#include <llvm/LLVMContext.h>
#include <llvm/Module.h>
#include <llvm/PassManager.h>
#include <llvm/Analysis/Verifier.h>
#include <llvm/Analysis/Passes.h>
#include <llvm/DataLayout.h>
#include <llvm/Transforms/Scalar.h>
#include <llvm/Support/TargetSelect.h>

extern "C" void test()
{
	puts("Hi!\n");
}

llvm::Module & makeLLVMModule(llvm::LLVMContext & context)
{
	auto & mod = *new llvm::Module("test", context);

	auto * test = mod.getOrInsertFunction("test", llvm::Type::getVoidTy(context), nullptr);
	auto * const puts = mod.getOrInsertFunction("puts", llvm::IntegerType::get(context, 32), llvm::IntegerType::get(context, 8)->getPointerTo(), nullptr);

	auto * const main = llvm::cast<llvm::Function>(mod.getOrInsertFunction("main", llvm::Type::getVoidTy(context), nullptr));

	{
		auto * block = llvm::BasicBlock::Create(context, "entry", main);
		llvm::IRBuilder<> builder(block);

		llvm::Value * helloWorld = builder.CreateGlobalStringPtr("hello world!\n");

		builder.CreateCall(test);
		builder.CreateCall(puts, helloWorld);
		builder.CreateRetVoid();
	}

	auto * const mul_add = llvm::cast<llvm::Function>(mod.getOrInsertFunction
		( "mul_add"
		, llvm::IntegerType::get(context, 32) // ret type
		, llvm::IntegerType::get(context, 32)
		, llvm::IntegerType::get(context, 32)
		, llvm::IntegerType::get(context, 32)
		, nullptr
		));

	{
		mul_add->setCallingConv(llvm::CallingConv::C);

		llvm::Function::arg_iterator args = mul_add->arg_begin();
		llvm::Value * x = args++;
		x->setName("x");
		llvm::Value * y = args++;
		y->setName("y");
		llvm::Value * z = args++;
		z->setName("z");

		auto * block = llvm::BasicBlock::Create(context, "entry", mul_add);
		llvm::IRBuilder<> builder(block);

		builder.CreateCall(main);

		auto * tmp = builder.CreateBinOp(llvm::Instruction::Mul, x, y, "tmp");
		auto * tmp2 = builder.CreateBinOp(llvm::Instruction::Add, tmp, z, "tmp2");

		builder.CreateRet(tmp2);
	}

	return mod;
}


int main(int argc, char**argv)
{
	llvm::InitializeNativeTarget();

	auto & context = llvm::getGlobalContext();

	auto & mod = makeLLVMModule(context);
	llvm::verifyModule(mod, llvm::PrintMessageAction);
	mod.dump();

	{
		auto * eb = llvm::EngineBuilder(&mod).create();

		auto * const main = llvm::cast<llvm::Function>(mod.getOrInsertFunction("main", llvm::Type::getVoidTy(context), nullptr));
		auto * f = (void (*)())eb->getPointerToFunction(main);

		f();
	}

	delete &mod;

	return 0;
}

