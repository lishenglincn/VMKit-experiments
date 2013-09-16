//===------------ ReactorInstrinsics.cpp
//
//             This file is part of the reactor project
//                Author: R-Core Team
//
//===---------------------------------------------------------------------===//

#include "ToyIntrinsics.h"

using namespace Toy;

void ToyIntrinsics::init(llvm::Module* M) {
	BaseIntrinsics::init(M);
	loadCommonTypes(M);
}

void ToyIntrinsics::loadCommonTypes(llvm::Module* selfModule) {
	typeInt64  = llvm::Type::getInt64Ty(selfModule->getContext());

#define z_getType(name) ({																			\
		llvm::Type* t = selfModule->getTypeByName("class." name);	\
		error_on(!t, "unable to find type: class." name);					\
		llvm::PointerType::get(t, 0);															\
})

	typePicture  = z_getType("Toy::Picture");
	typepPicture     = llvm::PointerType::get(typePicture, 0);

#undef z_getType

	toyFunctionType = llvm::FunctionType::get(typeInt64, typePicture, false);
}
