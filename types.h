#ifndef TYPES_H_
#define TYPES_H_

#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#define FNERROR	0
#define FNOK	1

/* Base types - All Java types are formed from 1, 2, and 4-byte base types */
typedef unsigned int u4;
typedef unsigned short u2;
typedef unsigned char u1;

extern int read_u4(FILE * stream, void * ptr);
extern int read_u2(FILE * stream, void * ptr);
extern int read_u1(FILE * stream, void * ptr);
extern int read_u1_string(FILE * stream, void * ptr, u2 length);

#endif
