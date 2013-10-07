#include <stdarg.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include "util.h"
#include <math.h>

using namespace Toy;

static void va_echo(const char* msg, const char* fmt, va_list va) {
	uint64_t n = 3 + strlen(msg);
	char buf[n];

	snprintf(buf, n, "[%s]", msg);
	fprintf(stderr, "%-15s", buf);
	vfprintf(stderr, fmt, va);
	fprintf(stderr, "\n");
}

void toyecho(const char* msg, const char* fmt, ...) {
	va_list va;
	va_start(va, fmt);
	va_echo(msg, fmt, va);
	va_end(va);
}

void do_toyfatal(const char* fn, uint64_t ln, const char* fct, const char* fmt, ...) {
	va_list va;
	va_start(va, fmt);
	va_echo("error", fmt, va);
	fprintf(stderr, "   at %s::%lu (%s)\n", fn, ln, fct);
	va_end(va);
	exit(42);
}

/**
 * Convertion entier (4 octets) LINUX en un entier SUN
 * @param i entier à convertir
 * @return entier converti
 */
int swap(int i) {
	int init = i;
	int conv;
	unsigned char *o, *d;

	o = ( (unsigned char *) &init) + 3;
	d = (unsigned char *) &conv;

	*d++ = *o--;
	*d++ = *o--;
	*d++ = *o--;
	*d++ = *o--;

	return conv;
}

unsigned char cos_composante(int i, double freq) {
  unsigned char o;
  double iD=(double) i;
  iD=cos(iD/255.0*2*M_PI*freq);
  iD+=1;
  iD*=128;

  o=(unsigned char) iD;
  return o;
}

#define COMPO_ROUGE(i)    cos_composante(i,13.0)
#define COMPO_VERT(i)     cos_composante(i,5.0)
#define COMPO_BLEU(i)     cos_composante(i+10,7.0)


void Rasterfile::saveRasterfile(char *name, Picture *p) {
	TOY_PARAM(p);
	FILE *fd;
	struct rasterfile ras;
	int i;
	unsigned char o;

	if ( (fd=fopen(name, "w")) == NULL ) {
		printf("erreur dans la creation du fichier %s \n",name);
		exit(1);
	}

	ras.ras_magic  = swap(RAS_MAGIC);
	ras.ras_width  = swap(p->width);	  /* largeur en pixels de l'image */
	ras.ras_height = swap(p->height);         /* hauteur en pixels de l'image */
	ras.ras_depth  = swap(8);	          /* profondeur de chaque pixel (1, 8 ou 24 )   */
	ras.ras_length = swap(p->width*p->height); /* taille de l'image en nb de bytes		*/
	ras.ras_type    = swap(RT_STANDARD);	  /* type de fichier */
	ras.ras_maptype = swap(RMT_EQUAL_RGB);
	ras.ras_maplength = swap(256*3);

	fwrite(&ras, sizeof(struct rasterfile), 1, fd);

	/* Palette de couleurs : composante rouge */
	i = 256;
	while( i--) {
		o= COMPO_ROUGE(i);
		fwrite( &o, sizeof(unsigned char), 1, fd);
	}

	/* Palette de couleurs : composante verte */
	i = 256;
	while( i--) {
		o= COMPO_VERT(i);
		fwrite( &o, sizeof(unsigned char), 1, fd);
	}

	/* Palette de couleurs : composante bleu */
	i = 256;
	while( i--) {
		unsigned char o= COMPO_BLEU(i);
		fwrite( &o, sizeof(unsigned char), 1, fd);
	}

	fwrite(p->data, p->size, sizeof(unsigned char), fd);
	fclose( fd);
}
