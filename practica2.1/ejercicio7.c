//Ej7. Escribir un programa que obtenga, con pathconf(3)
//informacion de configuración del sistema de ficheros e imprima, por ejemplo,
//número máximo de enlaces, el tamaño máximo de una ruta y el de un nombre de fichero
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){
	
	printf("MÁXIMO DE ENLACES: %li\n", fpathconf(0, _PC_LINK_MAX));
	printf("TAMAÑO MÁXIMO DE UNA RUTA: %li\n", fpathconf(0, _PC_PATH_MAX));
	printf("MÁXIMO DE NOMBRE DE FICHERO: %li\n", fpathconf(0, _PC_NAME_MAX));

	return 0;

}

