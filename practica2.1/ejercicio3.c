//Ej3 Escribir un programa que imprima todos los mensajes de error disponibles en el sistema. Considerar inicialmente que el límite de errores posibles es 255
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main()
{
	int i=0;
	for(i; i < 255; i++){
		printf("%i : %s\n", i, strerror(i));
	}
	return 1;
}

