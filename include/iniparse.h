#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/**
 * Typedef prototype for the callback
 */
typedef int (*callback)( char * section, char * key, char * value, void * data_structure );


/**
 * Parse input filename using handler function and provided structure
 */
int parse_ini (char * filename, void * data_struct, callback handler );
