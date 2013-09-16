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

	class Pixel /* : ? */ {
		public:
		double x, y;
	};

	class MandelPix /* : ? */ {
		public:
			static MandelPix* doNew(double x, double y);

			/*
			 * A completer
			 */
	};

	class Picture /* : ? */ {
		public:
			int size;
			MandelPix* buf;
			bool computed;

			double xMin, xMax, yMin, yMax, xScale, yScale;
			int width, height;

			/*
			 * Ce tableau sera "inliné" dans l'objet Picture lors du doNew()
			 */
			unsigned char data[1];

			static Picture* doNew(double xMin, double xMax, double yMin, double yMax, int width, int height);

			/*
			 * A completer
			 */
	};

	extern "C" int jitCompute(Picture* p);
}
#endif
