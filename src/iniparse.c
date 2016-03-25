#include"../include/iniparse.h"

#define ERROR(a) fprintf(stderr, "ERROR: %s\n", a);

static char *
rstrip(char * s){
	char * pointer = s + strlen(s);
	pointer--;
	while( isspace( *pointer ) && pointer > s ){
		*pointer='\0';
		pointer--;
	}
	return s;
}

static char *
lstrip(char * s){
	char * final = s + strlen(s);

	while( isspace( *s) && s<final )
		s++;
	return (char *) s;
}

static char *
find_char(char * s, char * ch_list){
	int i,j;
	int length = strlen(s);
	int charlist_l = strlen(ch_list);

	for( i=0; i < length; i++){
		for ( j=0; j < charlist_l; j++ ){
			if( s[i] == ch_list[j] && s[i] != '\0')
				return (char *) s + i;
		}
	}
	return (char *)NULL;
}

/**
 *	Parse input filename using handler function and provided structure
 *
 *	@returns 0 on success, -1 on file error and line number on parse error
 */
int
parse_ini (char * filename, void * data, callback handler ){
	FILE * config_file;
	config_file = fopen(filename, "r");
	if(config_file == NULL){
		ERROR("Unable to open file");
		return -1;
	}

	size_t size;
	char * line = NULL;
	char * start = NULL;
	char * end = NULL;

	char * section = NULL;
	char * key = NULL;
	char * value = NULL;
	ssize_t readed;

	// Current line
	int count = 1;

	while( (readed = getline(&line, &size, config_file)) != -1){

		start = rstrip( lstrip(line) );
		if( strlen(start) == 0 )
			continue; //Ignore empty lines

		// COMMENTS
		if( *start == ';' || *start == '#' )
			continue;

		// SECTION
		if( *start == '['){
			start = start+1;
			end = find_char(start, "]");

			if( end == NULL ){ //Doesn't close the section... error...
				ERROR( "Errored file" )
				return count;
			}

			*end = '\0'; //Section goes from _start to _end

			section = (char *) realloc( section, sizeof(char) * (end - start + 1) );
			if( !section ){
				ERROR( "Out of memory on section" );
				return count;
			}
			strcpy(section, start);
			continue;
		}

		// KEY [:=] VALUE PAIR
		end = find_char ( start, ":=" );
		if( *end != ':' && *end != '=' ){
			ERROR( "No : or = in key - value line" );
			return count;
		}
		// get the key
		*end = '\0';
		start = rstrip (start);
		key = (char *) realloc( key, sizeof(char) * (end - start + 1) );
		if( !key ){
			ERROR( "Out of memory on key" );
			return count;
		}
		strcpy( key, start );

		// get the value
		start = end + 1;
		start = lstrip (start);
		end = start + strlen(start)-1;
		value = (char *) realloc( value, sizeof(char) * (end - start + 1) );
		if( !value ){
			ERROR( "Out of memory on value" );
			return count;
		}
		strcpy( value, start );

		// Call user defined handler
			// (send section safely for next iteration)
		char * section_copy = (char *) malloc( sizeof(char) * strlen(section) );
		if( ! section_copy){
			ERROR( "Out of memory on section copy" );
			return count;
		}
		strcpy(section_copy, section);
		if( handler( section_copy, key, value, data )){
			ERROR( "Parse error on callback function" );
			return count;
		}
		free(section_copy);
		count ++;
	}

	if(key !=NULL)
		free(key);
	if(value !=NULL)
		free(value);
	if(section !=NULL)
		free(section);
	free(line);
	fclose(config_file);
	return 0;
}
