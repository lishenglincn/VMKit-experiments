// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
//===------------ Evaluator.h
//
//             This file is part of the reactor project
//                Author: R-Core Team
//
//===---------------------------------------------------------------------===//
#ifndef _PIXEL_H_
#define _PIXEL_H_

#include "ToyRoot.h"
#include "util.h"

namespace Toy {
	class ToyRoot;

	class Pixel : public ToyRoot {
		public:
		double x, y;
	};

	class MandelPix : public Pixel {
		public:
			static MandelPix* doNew(double x, double y);

			virtual int compute() override;
			virtual void tracer(word_t closure) override;
			virtual void print() override;
	};

	class Picture : public ToyRoot {
		public:
			int size;
			MandelPix* buf;
			bool computed;

			double xMin, xMax, yMin, yMax, xScale, yScale;
			int width, height;

			unsigned char data[16 * 1048 * 1024];

			static Picture* doNew(double xMin, double xMax, double yMin, double yMax, int width, int height);

			virtual int compute() override;
			virtual void tracer(word_t closure) override;
			virtual void print() override;
	};

	extern "C" int jitCompute(Picture* p);
}
#endif
