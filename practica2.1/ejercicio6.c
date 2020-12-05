#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){
	if(sysconf(_SC_ARG_MAX) == -1 || sysconf(_SC_CHILD_MAX) == -1 || sysconf(_SC_OPEN_MAX) == -1){
		printf("Error: %s\n", errno, strerror(errno));
		return -1;
	}
	printf("LONG MAXIMA ARGUMENTOS: %li\n", sysconf(_SC_ARG_MAX));
	printf("MÁXIMO DE HIJOS: %li\n", sysconf(_SC_CHILD_MAX));
	printf("MÁXIMO DE FICHEROS: %li\n", sysconf(_SC_OPEN_MAX));

	return 0;

}
