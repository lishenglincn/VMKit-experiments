// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
//===------------ Any.h
//
//             This file is part of the reactor project
//                Author: R-Core Team
//
//===---------------------------------------------------------------------===//

#ifndef _ANY_H_
#define _ANY_H_

#include <cstdio>
#include <cstring>

#include "vmkit/Locks.h"
#include "vmkit/System.h"
#include "VmkitGC.h"
#include "vmkit/Allocator.h"

namespace Toy {

	/*
	 * ToyObject root type, must extend gc class provided by VMKit.
	 */
	class ToyRoot: public gc {
	protected:
		/*
		 * This constructor is never called
		 */
		ToyRoot() {assert(false);}

		/*
		 * This is the operator which is called to instantiate ToyObjects
		 */
		template <class T>
		void* operator new(size_t sz, int param=0) {
			void* res = 0;
			llvm_gcroot(res, 0);
			static T o;
			res = gc::operator new(sz, o.getVirtualTable());
			return res;
		}

	public:


		/*
		 * GC related methods to identify roots and trace them during garbage collection.
		 */
		static void markAndTrace(void* source, void* ptr, word_t closure){
			vmkit::Collector::markAndTrace(source, ptr, closure);
		}
		static void markAndTraceRoot(void* ptr, word_t closure){
			vmkit::Collector::markAndTraceRoot(ptr, ptr, closure);
		}

		/***************************************************
		 *               VMKit Virtual Method for GC       *
		 ***************************************************/
		/*
		 *  Trace function used for GC Collection. Mark every collectible objects
		 *  contained in this one.
		 */
		virtual void tracer(word_t closure);

		/***************************************************
		 *               Toy Virtual Methods               *
		 ***************************************************/

		/*
		 * Print method for ToyObject.
		 */
		virtual void print();
		virtual int compute() = 0;

	};
}

#endif
