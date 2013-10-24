#pragma once

#include <VmkitGC.h>

namespace vm { namespace core {

	class Root : public gc
	{
	public:
		template<class T>
		void * operator new(const size_t size, int param = 0)
		{
			void * res = nullptr;
			llvm_gcroot(res, 0);
			res = gc::operator new(size, nullptr);

			static T o;
			VirtualTable::setVirtualTable((gc *)res, const_cast<VirtualTable *>(VirtualTable::getVirtualTable(&o)));

			return res;
		}

		static void markAndTrace(void * src, void * ptr, word_t closure)
		{
			vmkit::Collector::markAndTrace(src, ptr, closure);
		}

		static void markAndTraceRoot(void * ptr, word_t closure)
		{
			vmkit::Collector::markAndTraceRoot(ptr, ptr, closure);
		}

	private:
		Root() = delete;
		Root(const Root &) = delete;
		void operator=(const Root &) = delete;
	};

}}

