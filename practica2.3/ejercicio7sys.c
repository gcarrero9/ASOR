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
	int longitud=1;
	int i=1;
	for(i; i < argc; i++){
		longitud += strlen(argv[i]) + 1;
	}
	char *sys = malloc(sizeof(char)*longitud);
	strcpy(sys, "");

	for(i = 1; i < argc; i++){
		strcat(sys, argv[i]);
		strcat(sys, " ");
	}

	if(system(sys) == -1){
		printf("Error\n");
	}
	printf("El comando terminó de ejecutarse\n");

	return 0;
}


