// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
//===------------ RPrinter.cpp
//
//             This file is part of the reactor project
//                Author: R-Core Team
//
//===---------------------------------------------------------------------===//

#include "ToyRoot.h"
#include "Pixel.h"
#include "util.h"

using namespace Toy;


void Picture::print()
{
	asSelf(Picture);
	
	fprintf(stderr, "Picture::print()\n");
	if(computed)
		Rasterfile::saveRasterfile((char*)"mandelbrot.ras", self);
}

void MandelPix::print()
{
	fprintf(stderr, "MandelPix::print()\n");
}
