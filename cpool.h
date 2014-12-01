#ifndef CPOOL_H_
#define CPOOL_H_

#include "types.h"

/* Constant pool tags */
#define CONSTANT_CLASS				7
#define CONSTANT_FIELDREF			9
#define CONSTANT_METHODREF			10
#define CONSTANT_INTERFACEMETHODREF	11
#define CONSTANT_STRING				8
#define CONSTANT_INTEGER			3
#define CONSTANT_FLOAT				4
#define CONSTANT_LONG				5
#define CONSTANT_DOUBLE				6
#define CONSTANT_NAMEANDTYPE		12
#define CONSTANT_UTF8				1
#define CONSTANT_METHODHANDLE		15
#define CONSTANT_METHODTYPE			16
#define CONSTANT_INVOKEDYNAMIC		18

#pragma pack(push, 1)

typedef struct cp_info_tag {
    u1 tag;
    u1* info;
} cp_info;

/* Constant pool types and loaders */
typedef struct CONSTANT_Class_info_tag {
    u1 tag;
    u2 name_index;
} CONSTANT_Class_info;

typedef struct CONSTANT_String_info_tag {
    u1 tag;
    u2 string_index;
} CONSTANT_String_info;

typedef struct CONSTANT_MethodType_info_tag {
    u1 tag;
    u2 descriptor_index;
} CONSTANT_MethodType_info;

typedef struct CONSTANT_MethodHandle_info_tag {
    u1 tag;
    u1 reference_kind;
    u2 reference_index;
} CONSTANT_MethodHandle_info;

typedef struct CONSTANT_Fieldref_info_tag {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
} CONSTANT_Fieldref_info;

typedef struct CONSTANT_Methodref_info_tag {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
} CONSTANT_Methodref_info;

typedef struct CONSTANT_InterfaceMethodref_info_tag {
    u1 tag;
    u2 class_index;
    u2 name_and_type_index;
} CONSTANT_InterfaceMethodref_info;

typedef struct CONSTANT_NameAndType_info_tag {
    u1 tag;
    u2 name_index;
    u2 descriptor_index;
} CONSTANT_NameAndType_info;

typedef struct CONSTANT_InvokeDynamic_info_tag {
    u1 tag;
    u2 bootstrap_method_attr_index;
    u2 name_and_type_index;
} CONSTANT_InvokeDynamic_info;

typedef struct CONSTANT_Integer_info_tag {
    u1 tag;
    u4 bytes;
} CONSTANT_Integer_info;

typedef struct CONSTANT_Float_info_tag {
    u1 tag;
    union {	
    	float bytesf;
		u4 bytesu;
	} val;
} CONSTANT_Float_info;

typedef struct CONSTANT_Long_info_tag {
    u1 tag;
    union {
		u4 high_bytes;
		u4 low_bytes;
		long long_bytes;
	} val;
} CONSTANT_Long_info;

typedef struct CONSTANT_Double_info_tag {
    u1 tag;
    union {
		u4 high_bytes;
		u4 low_bytes;
		long long_bytes;
		double double_bytes;
    } val;
} CONSTANT_Double_info;

typedef struct CONSTANT_Utf8_info_tag {
    u1 tag;
    u2 length;
    u1* bytes;	/*[length] */
} CONSTANT_Utf8_info;

#pragma pack(pop)

extern int load_constant_pool(FILE * stream, unsigned cpool_count, cp_info** cpool);
extern void free_constant_pool(unsigned cpool_count, cp_info** cpool);

#endif
