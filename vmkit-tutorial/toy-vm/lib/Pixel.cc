// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
//===------------ Evaluator.h
//
//             This file is part of the reactor project
//                Author: R-Core Team
//
//===---------------------------------------------------------------------===//

#include "Pixel.h"

using namespace Toy;

#define NB_ITER 255

Picture* Picture::doNew(double _xMin, double _xMax, double _yMin, double _yMax, int _width, int _height){
	TOY_VAR(Picture *, res);
	res = static_cast<Picture *>(operator new<Picture>(sizeof(Picture)));
	
	res->size = _width*_height;
	res->xMin = _xMin;
	res->xMax = _xMax;
	res->yMin = _yMin;
	res->yMax = _yMax;
	res->width = _width;
	res->height = _height;
	res->computed = false;
	res->xScale = (_xMax - _xMin) / static_cast<double>(_width);
	res->yScale = (_yMax - _yMin) / static_cast<double>(_height);

	return res;
}

int Picture::compute(){
	asSelf(Picture);
	
	fprintf(stderr, "Picture::compute()\n");

	double curX = self->xMin;
	double curY = self->yMax;
	double _xMax = self->xMax;
	double _xMin = self->xMin;
	double _xScale = self->xScale;
	double _yScale = self->yScale;
	int _size = self->size;

	for(int i = 0; i < _size; i++)
	{
		TOY_VAR(MandelPix *, pix);
		pix = MandelPix::doNew(curX, curY);

		vmkit::Collector::objectReferenceWriteBarrier(self, (gc **)&(self->buf), pix);
		self->data[i] = static_cast<unsigned char>(self->buf->compute());

		curX += _xScale;
		if(curX >= _xMax)
		{
			curY -= _yScale;
			curX = _xMin;
		}
	}

	computed = true;
	return 0;
}

MandelPix * MandelPix::doNew(double x, double y)
{
	TOY_VAR(MandelPix *, res);
	res = static_cast<MandelPix *>(operator new<MandelPix>(sizeof(MandelPix)));
	res->x = x;
	res->y = y;
	return res;
}

int MandelPix::compute(){
	asSelf(MandelPix);

	int _value = 0;
	double x_orig = self->x;
	double y_orig = self->y;
	double Z_re = x_orig;
	double Z_im = y_orig;
	double Z_re2 = x_orig*x_orig;
	double Z_im2 = y_orig*y_orig;

	while((Z_re2 + Z_im2 < 4) && (_value < NB_ITER)) {
		Z_im = 2*Z_re*Z_im + y_orig;
		Z_re = Z_re2 - Z_im2 + x_orig;
		Z_re2 = Z_re*Z_re;
		Z_im2 = Z_im*Z_im;
		_value++;
	}
	return _value;
}

	/*
	 * A Decommenter des que la méthode compute de la classe Picture
	 * est implémentée.
	 */
extern "C" int64_t jitCompute(Picture* p){
	TOY_PARAM(p);
	p->compute();
	return 0;
}
