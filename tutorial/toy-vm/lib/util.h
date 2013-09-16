// -*- c-basic-offset: 2 default-tab-width: 2 indent-tabs-mode: t -*-
// vim: autoindent tabstop=2 noexpandtab shiftwidth=2 softtabstop=2
#ifndef __UTIL_H
#	define __UTIL_H

#if defined(__GNUC__) && !defined(inline)
#	define inline inline __attribute__((always_inline))
#endif

#include "Pixel.h"

#define TOY_VAL(__type, __var, __val)\
		__type __var = NULL;\
		llvm_gcroot(__var, 0); \
		__var = __val

#define TOY_VAR(__type, __var)\
		__type __var = NULL;\
		llvm_gcroot(__var, 0)

#define TOY_PARAM(__var)\
		llvm_gcroot(__var, 0)

#define asSelf(T)\
		T* self = this;\
		llvm_gcroot(self, 0)

extern void toyecho(const char* msg, const char* fmt, ...)__attribute__((noinline));
void do_toyfatal(const char* fn, uint64_t ln, const char* fct, const char* fmt, ...) __attribute__((noreturn));

#define warning(...)\
		toyecho("warning", __VA_ARGS__)
#define toyfatal(...)\
		do_toyfatal(__FILE__, __LINE__, __PRETTY_FUNCTION__, __VA_ARGS__)
#define error_on(__test, ...)\
		if(__test)\
		toyfatal("assertion failed '" #__test "':\t" __VA_ARGS__)

#define Assert(__test, ...)\
		error_on(!(__test), __VA_ARGS__)

#define nyi_fatal()\
		toyfatal("not yet implemented")

#define nyi()					\
		({ static int z_nyi=0; if(!z_nyi) { z_nyi=1; fprintf(stderr, "Not yet implemented at %s::%d (%s)\n", __FILE__, __LINE__, __PRETTY_FUNCTION__); }})

#define PrintNewLine()\
		puts("")

/*
 *
 * PICTURE RELATED FUNCTIONS
 *
 */
struct rasterfile {
		int	ras_magic;		/* magic number */
		int	ras_width;		/* width (pixels) of image */
		int	ras_height;		/* height (pixels) of image */
		int	ras_depth;		/* depth (1, 8, or 24 bits) of pixel */
		int	ras_length;		/* length (bytes) of image */
		int	ras_type;		/* type of file; see RT_* below */
		int	ras_maptype;		/* type of colormap; see RMT_* below */
		int	ras_maplength;		/* length (bytes) of following map */
		/* color map follows for ras_maplength bytes, followed by image */
};
#define	RAS_MAGIC	0x59a66a95
/* Sun supported ras_type's */
#define RT_OLD		0	/* Raw pixrect image in 68000 byte order */
#define RT_STANDARD	1	/* Raw pixrect image in 68000 byte order */
#define RT_BYTE_ENCODED	2	/* Run-length compression of bytes */
#define RT_FORMAT_RGB	3	/* XRGB or RGB instead of XBGR or BGR */
#define RT_FORMAT_TIFF	4	/* tiff <-> standard rasterfile */
#define RT_FORMAT_IFF	5	/* iff (TAAC format) <-> standard rasterfile */
#define RT_EXPERIMENTAL 0xffff	/* Reserved for testing */

/* Sun registered ras_maptype's */
#define RMT_RAW		2
/* Sun supported ras_maptype's */
#define RMT_NONE	0	/* ras_maplength is expected to be 0 */
#define RMT_EQUAL_RGB	1	/* red[ras_maplength/3],green[],blue[] */


namespace Toy {
	class Picture;
	class Rasterfile{
		public:
			/**
			 *  Sauvegarde le tableau de données au format rasterfile
			 *  8 bits avec une palette de 256 niveaux de gris du blanc (valeur 0)
			 *  vers le noir (255)
			 *    @param nom Nom de l'image
			 *    @param largeur largeur de l'image
			 *    @param hauteur hauteur de l'image
			 *    @param p pointeur vers tampon contenant l'image
			 */
			static void saveRasterfile(char *name, Picture *p);
	};
}
#endif
