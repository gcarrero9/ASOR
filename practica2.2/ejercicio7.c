#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[]){
	mode_t mascara = umask(027);
	
	int fichero= open(argv[1], O_CREAT, 0645);

	if(fichero == -1){
		perror("Error al crear fichero");
	}

	printf("Valor descriptor: %i\n", fichero);
	
	return 1;
}

