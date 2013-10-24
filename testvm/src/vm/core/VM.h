#pragma once

#include <vmkit/VirtualMachine.h>

namespace vm { namespace core {

	class VM : public vmkit::VirtualMachine
	{
	public:
		explicit VM(vmkit::BumpPtrAllocator &, vmkit::CompiledFrames **);

		virtual void traceObject(gc * object, word_t closure) override;
		virtual void * getType(gc * header) override;
		virtual void setType(gc * header, void * type) override;
		virtual size_t getObjectSize(gc * object) override;
		virtual void printMethod(vmkit::FrameInfo * FI, word_t ip, word_t addr) override;
		virtual void nullPointerException() override;
		virtual void stackOverflowError() override;

		virtual void runApplication(int argc, char ** argv) override;

	private:
		static void mainStart(vmkit::Thread *);

	private:
		VM(const VM &) = delete;
		void operator=(const VM &) = delete;
	};

}}

