//Ej7.Escribir 2 versiones, una con system(3) y otra con execvp(3) de un programa que ejecute otro programa que se pasará como argumento por línea de comandos.
//En cada caso, se debe imprimir la cadena "El comando terminó de ejecutarse" después de la ejecución.
//¿En qué casos se imprime la cadena? Por qué?

#include <stdio.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <stdlib.h>
#include <string.h>

int main(int argc, char **argv){
	if(argc < 2){
		printf("Error\n");
		return -1;
	}
	if(execvp(argv[1], argv + 1) == -1){
		printf("Error. No se ha ejecutado correctamente.\n");
	}
	printf("El comando terminó de ejecutarse\n");
	return 0;
}

