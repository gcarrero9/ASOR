//Ej 2 Imprimir el codigo de error generado por la llamada del código anterior, tanto su versión numérica como la cadena asociada
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

int main()
{
	if(setuid(0) == -1){
		//perror("error");
		printf("setuid error: %s\n", errno, strerror(errno));
	}
	return 1;
}

