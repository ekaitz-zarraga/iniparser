#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<ctype.h>

/**
 * Typedef prototype for the callback
 */
typedef int (*callback)( char * section, char * key, char * value, void * data_structure );

/**
 * Insert \0 in all the space values on the end of the string
 */
static char * rstrip(char * s);


/**
 * Return the pointer to the first non space character
 */
static char * lstrip(char * s);


/**
 * Find first appearance of characters in string
 */
static char * find_char(char * s, char * ch_list);


/**
 * Parse input filename using handler function and provided structure
 */
int parse_ini (char * filename, void * data_struct, callback handler );
