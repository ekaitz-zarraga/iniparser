#include<stdio.h>
#include"../include/iniparse.h"

// Compile me with:
// examples$ gcc main.c -L.. -liniparser -o main.out
// (The library must be compliled first)

typedef struct{
	int a;
} data_structure;

// Callback function
int process( char * section, char * key, char * value, void * data_struct){
	data_structure *data = (data_structure *)data_struct;
	printf("MOTHERFUCKER:%s\n", section);
	*section = 't'; // won't destroy next sections name, it's a copy
	return 0;
}

int main(int argc, char * argv[]){
	data_structure * data;
	return parse_ini("example.ini", data, process);
}
