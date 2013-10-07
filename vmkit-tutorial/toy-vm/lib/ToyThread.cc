// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
//===------------ Evaluator.cpp
//
//             This file is part of the toyVM project
//                Author: R-Core Team
//
//===---------------------------------------------------------------------===//

#include "util.h"
#include "ToyThread.h"
#include "ToyVM.h"
#include "ToyCompiler.h"
#include "ToyJITCompiler.h"
#include "Pixel.h"

using namespace Toy;

ToyThread::ToyThread(ToyVM * vm)
	: _vm(vm)
{
	this->MyVM = vm;
}

ToyVM* ToyThread::vm()
{
	return _vm;
}

typedef int (*jitPtr)(Picture*);

/*
 * Mandelbrot computing here
 *
 * Parametres recommandés pour l'objet Picture (Question 3.3) :
 * Picture::doNew(-2, 1, -1, 1, 1900, 1200)
 *
 */
void ToyThread::execute(){
	bool jit = true; // will be passed as argument
//	if(vm()->argumentsInfo.jit){
//		/*
//		 * Question 4.3
//		 * Appeler le compilateur JIT pour générer un pointeur vers une fonction
//		 * qui calcul la fractale de Mandelbrot.
//		 *
//		 * Note : un appel à jitCompile est nécéssaire
//		 *
//		 */
//	}
//	else {
//		/*
//		 * A completer, appel à compute
//		 */
//		}
//
//	/*
//	 * A completer, Appel à Picture::print
//	 */

	{
		TOY_VAR(Picture *, p);
		p = Picture::doNew(-3, 1, -1, 1, 4096, 2048);
		p->compute();
		p->print();
	}
}
