// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
//===------- RIntrinsics.h - The Reactor LLVM instrinsics ----------------===//
//
//                            The VMKit project
//
// This file is distributed under the Purdue University Open Source
// License. See LICENSE.TXT for details.
//
//===----------------------------------------------------------------------===//

#ifndef _RINTRINSICS_H_
#define _RINTRINSICS_H_

#include <llvm/IR/LLVMContext.h>
#include <llvm/IR/Module.h>
#include <llvm/IR/DerivedTypes.h>
#include "vmkit/JIT.h"
#include "util.h"

namespace Toy {

	class ToyIntrinsics : public vmkit::BaseIntrinsics {
	public:

		llvm::FunctionType*        toyFunctionType;

		llvm::Type*                typePicture;
		llvm::Type*                typepPicture;

		llvm::Type*                typeInt64;

	  void init(llvm::Module* M);
	  void loadCommonTypes(llvm::Module* selfModule);
	};

}

#endif
