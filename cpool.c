#include "cpool.h"

/* Structs for the convenience of reading in similar formats */
#pragma pack(push, 1)

struct io_format_12 {
	u1 tag;
	u2 first;
};

struct io_format_122 {
	u1 tag;
	u2 first;
	u2 second;
};

struct io_format_14 {
	u1 tag;
	u4 first;
};

struct io_format_18 {
	u1 tag;
	u1 upper;
	u2 lower;
};

#pragma pack(pop)

int load_constant_pool(FILE * stream, unsigned cpool_count, cp_info** cpool) {
	int i = 0, cpcount = cpool_count - 1;
	cp_info* lcpool = NULL;
	
	if (NULL == (*cpool = malloc(sizeof(cp_info) * cpcount)))
		return FNERROR;
		
	for (lcpool = *cpool; i < cpcount; ++i, ++lcpool) {
		read_u1(stream, &lcpool->tag);
		
		switch (lcpool->tag) { /* Fallthroughs intentional */
		
			/* 1-2 packed structures */
			case CONSTANT_CLASS:
			case CONSTANT_STRING:
			case CONSTANT_METHODTYPE: {
				struct io_format_12* cpip = (struct io_format_12*)lcpool;
				read_u2(stream, &cpip->first);
				}
				break;
				
			/* 1-1-2 packed structures */
			case CONSTANT_METHODHANDLE: {
				CONSTANT_MethodHandle_info* cpip = (CONSTANT_MethodHandle_info*)lcpool;
				read_u1(stream, &cpip->reference_kind);
				read_u2(stream, &cpip->reference_index);
				}
				break;
				
			/* 1-2-2 packed structures */
			case CONSTANT_FIELDREF:
			case CONSTANT_METHODREF:
			case CONSTANT_INTERFACEMETHODREF:
			case CONSTANT_NAMEANDTYPE:
			case CONSTANT_INVOKEDYNAMIC: {
				struct io_format_122* cpip = (struct io_format_122*)lcpool;
				read_u2(stream, &cpip->first);
				read_u2(stream, &cpip->second);
				}
				break;
				
			/* 1-4 packed structures */
			case CONSTANT_INTEGER:
			case CONSTANT_FLOAT: {
				struct io_format_14* cpip = (struct io_format_14*)lcpool;
				read_u4(stream, &cpip->first);
				}
				break;
				
			/* 1-8-byte packed structures */
			case CONSTANT_LONG:
			case CONSTANT_DOUBLE: {
				struct io_format_18* cpip = (struct io_format_18*)lcpool;
				read_u4(stream, &cpip->upper);
				read_u4(stream, &cpip->lower);
				}
				break;
				
			/* Variable */
			case CONSTANT_UTF8: {
				CONSTANT_Utf8_info* cpip = (CONSTANT_Utf8_info*)lcpool;
				read_u2(stream, &cpip->length);
				if (NULL == (cpip->bytes = malloc(sizeof(u1) * cpip->length))) {
					return FNERROR;
				}
				read_u1_string(stream, cpip->bytes, cpip->length);
				cpip->bytes[0] = cpip->bytes[0];
				}
				break;
				
			default: return FNERROR;
		}
	}
	return FNOK;
}
