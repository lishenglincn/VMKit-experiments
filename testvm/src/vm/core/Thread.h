#pragma once

#include <MutatorThread.h>

namespace vm { namespace core {

	class VM;

	class Thread : public vmkit::MutatorThread
	{
	public:
		explicit Thread(VM &);

	private:
		Thread(const Thread &) = delete;
		void operator=(const Thread &) = delete;
	};

}}

