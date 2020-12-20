//Ej 13. Modificar el programa anterior para que además de escribir en el fichero la salida estándar también se escriba la salida estándar de error.
//Comprobar el funcionamiento incluyendo varias sentencias que impriman en ambos flujos.

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
		perror("Error en duplicado");
		return -1;
	}

	printf("%s\n", argv[1]);

	int fd3 = dup2(fd, 2); //salida de error 2

	if(fd3 == -1){
                perror("Error");
                return -1;
        }

	printf("%s\n", argv[1]);
	return 1;
}

