#include "cpool.h"


int load_constant_pool(FILE * stream, cp_info** cpool) {
	int i = 0, cpcount = cfd->constant_pool_count - 1;
	
	if (NULL == (cfd->constant_pool = malloc(sizeof(cp_info*) * cpcount)))
		return FNERROR;
		
	for (; i < cpcount; ++i) {
		cfd->constant_pool[i].info = (u1*)malloc(sizeof(cp_info));
		read_u1(stream, &cfd->constant_pool[i].tag);
		
		switch (cfd->constant_pool[i].tag) {
			case CONSTANT_CLASS:
			case CONSTANT_FIELDREF:
			case CONSTANT_METHODREF:
			case CONSTANT_INTERFACEMETHODREF:
			case CONSTANT_STRING:
			case CONSTANT_INTEGER:
			case CONSTANT_FLOAT:
			case CONSTANT_LONG:
			case CONSTANT_DOUBLE:
			case CONSTANT_NAMEANDTYPE:
			case CONSTANT_UTF8:
			case CONSTANT_METHODHANDLE:
			case CONSTANT_METHODTYPE:
			case CONSTANT_IINVOKEDYNAMIC:
			default: return FNERROR;
		}
	}
	return FNOK;
}