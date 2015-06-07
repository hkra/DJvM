/*
 *	Functions relating to types. This is intended to run on x86 machines, so endian
 *	conversions are done as necessary...okay, I admit it. I just wrote this because
 *	I want a commit for today :(
 */

#include "types.h"

int read_u4(FILE * stream, void * ptr) {
	int nread = fread(ptr, sizeof(u4), 1, stream);
/*	u4 swapc = *(u4*)ptr;
	swapc = (swapc & 0x000000FF) << 24 |
			(swapc & 0x0000FF00) << 8 |
			(swapc & 0x00FF0000) >> 8 |
			(swapc & 0xFF000000) >> 24;
	*(u4*)ptr = swapc;*/
	return nread;
}

int read_u2(FILE * stream, void * ptr) {
	int nread = fread(ptr, sizeof(u2), 1, stream);
	u2 swapc = *(u2*)ptr;
	*(u2*)ptr = (swapc >> 8) | (swapc << 8);
	return nread;
}

int read_u1(FILE * stream, void * ptr) {
	return fread(ptr, sizeof(u1), 1, stream);
}

int read_u1_string(FILE * stream, void * ptr, u2 length) {
	return fread(ptr, sizeof(u1), length, stream);
}
