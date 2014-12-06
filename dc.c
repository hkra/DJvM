#include <stdio.h>
#include <stdlib.h>
#include <memory.h>

#include "types.h"
#include "cpool.h"

#define MAGIC_NUMBER	0xCAFEBABE

/* Access flags */
#define ACC_PUBLIC		0x0001	/* Declared public; may be accessed from outside its package. */
#define ACC_FINAL		0x0010	/* Declared final; no subclasses allowed. */
#define ACC_SUPER		0x0020	/* Treat superclass methods specially when invoked by the invokespecial instruction. */
#define ACC_INTERFACE	0x0200	/* Is an interface, not a class. */
#define ACC_ABSTRACT	0x0400	/* Declared abstract; must not be instantiated. */
#define ACC_SYNTHETIC	0x1000	/* Declared synthetic; not present in the source code. */
#define ACC_ANNOTATION	0x2000	/* Declared as an annotation type. */
#define ACC_ENUM		0x4000	/* Declared as an enum type. */
 
/* SS4.7 - Attributes */
typedef struct attribute_info_tag {
    u2 attribute_name_index;
    u4 attribute_length;
    u1* info;							/* [attribute_length] */
} attribute_info;

/* SS4.5 - Fields */
typedef struct field_info_tag {
    u2             	access_flags;
    u2             	name_index;
    u2             	descriptor_index;
    u2             	attributes_count;
    attribute_info* attributes;			/* [attributes_count] */
} field_info;

/* SS4.6 - Methods */
typedef struct method_info_tag {
    u2             	access_flags;
    u2             	name_index;
    u2             	descriptor_index;
    u2             	attributes_count;
    attribute_info* attributes;			/* [attributes_count] */
} method_info;

/* The class file in all it weirdness */
typedef struct class_file_tag {
    u4             magic;
    u2             minor_version;
    u2             major_version;
    u2             constant_pool_count;
    cp_info*       constant_pool;  	/*[constant_pool_count-1]*/
    u2             access_flags;
    u2             this_class;
    u2             super_class;
    u2             interfaces_count;
    u2*            interfaces; 		/*[interfaces_count]*/
    u2             fields_count;
    field_info*    fields;			/*[fields_count]*/
    u2             methods_count;
    method_info*   methods;			/*[methods_count]*/
    u2             attributes_count;
    attribute_info* attributes;		/*[attributes_count]*/
} ClassFile;

void free_class_memory(ClassFile * cfd) {
	/* for now do nothing because we just exit the process after run :/ */
}

void print_class_info(const ClassFile * const cfd) {
	printf("Java class file (version %hu.%hu)\n", cfd->major_version, cfd->minor_version);
	printf("Constant pool count: %hu\n", cfd->constant_pool_count);
}

int main(int argc, char * argv[]) {
	int error = 0, i;
	FILE* class_file_handle = NULL;
	ClassFile class_file_data;

	if (argc != 2) {
		printf("dc - Java Class Decompiler\n");
		printf("\tUsage:\tdc {filename}.class\n\n");
		goto drykill;
	}

	if (NULL == (class_file_handle = fopen(argv[1], "r"))) {
		fprintf(stderr, "Error: No such file exists (\"%s\")\n", argv[1]);
		error = 1;
		goto drykill;
	}

	memset(&class_file_data, 0, sizeof(ClassFile));
	
	if (!read_u4(class_file_handle, &class_file_data.magic) || class_file_data.magic != MAGIC_NUMBER) {
		fprintf(stderr, "Error: \"%s\" is not a Java class file.\n", argv[1]);
		error = 1;
		goto releasekill;
	}
	
	read_u2(class_file_handle, &class_file_data.minor_version);
	read_u2(class_file_handle, &class_file_data.major_version);
	read_u2(class_file_handle, &class_file_data.constant_pool_count);
				
	/* TODO: check final size of all stuff read. If not right, abort */
	load_constant_pool(class_file_handle, class_file_data.constant_pool_count, &class_file_data.constant_pool);
	
	read_u2(class_file_handle, &class_file_data.access_flags);
	read_u2(class_file_handle, &class_file_data.this_class);
	read_u2(class_file_handle, &class_file_data.super_class);
	read_u2(class_file_handle, &class_file_data.interfaces_count);
				 
	/* Read interface list */
	if (NULL == (class_file_data.interfaces = malloc(sizeof(u2) * class_file_data.interfaces_count))) {
		/* TODOL free constant pool memory */
		fprintf(stderr, "Error: malloc failure (%s, %d)\n", __FILE__, __LINE__);
		error = 1;
		goto releasekill;
	}
	
	for (i = 0; i < class_file_data.interfaces_count; ++i) {
		read_u2(class_file_handle, &class_file_data.interfaces[i]);
	}
	
	read_u2(class_file_handle, &class_file_data.fields_count);
				 
	print_class_info(&class_file_data);
	
releasekill:
	fclose(class_file_handle);
	free_class_memory(&class_file_data);
drykill:	
	return error;
}
