// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
//===------------ VirtualTables.cpp
//
//             This file is part of the reactor project
//                Author: R-Core Team
//
//===---------------------------------------------------------------------===//

#include "ToyVM.h"
#include "Pixel.h"
#include "ToyThread.h"

using namespace Toy;


/******************************************************************************
 *                                  Tracers                                   *
 ******************************************************************************/

void MandelPix::tracer(word_t closure)
{
	fprintf(stderr, "MandelPix::tracer()\n");
}

void Picture::tracer(word_t closure)
{
	fprintf(stderr, "Picture::tracer()\n");

	vmkit::Collector::markAndTrace(this, &(this->buf), closure);
}
