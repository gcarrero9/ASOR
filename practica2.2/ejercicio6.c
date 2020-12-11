#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>

int main(int argc, char* argv[]){
	
	int fichero= open(argv[1], O_CREAT, 0777 & ~027);

	if(fichero == -1){
		perror("Error al crear fichero");
	}

	printf("Valor descriptor: %i\n", fichero);
	
	return 1;
}

