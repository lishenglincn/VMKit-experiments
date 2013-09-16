// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
//===------------ Evaluator.h
//
//             This file is part of the reactor project
//                Author: R-Core Team
//
//===---------------------------------------------------------------------===//

#ifndef _EVALUATOR_H_
#define _EVALUATOR_H_

#include "MutatorThread.h"
#include "vmkit/System.h"
#include "vmkit/Locks.h"

namespace Toy {
	class ToyVM;

	class ToyThread /* : ? */ {
		public:
		ToyThread(ToyVM* vm);
		ToyVM* vm();
		void execute();
	};
}

#endif
