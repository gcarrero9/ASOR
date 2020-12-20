//Ej 12. Escribir un programa que redirija la salida estándar a un fichero cuya ruta se pasa como primer argumento.
//Probar haciendo que el programa escriba varias cadenas en la salida estándar.

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char **argv){
	int fd;

	if((fd = open(argv[2], O_CREAT | O_TRUNC | O_RDWR, 0644)) == -1){
		perror("Error");
		return -1;
	}
	
	int fd2 = dup2(fd, 1); //salida estándar 1

	close(fd); //Recomendable cerrar los ficheros

	if(fd2 == -1){
		perror("Duplicado");
		return -1;
	}
	printf("%s\n", argv[1]);
	return 1;
}

