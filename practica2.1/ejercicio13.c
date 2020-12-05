//Ej13. Escribir un programa que mida, en microsegundos usando la función gettimeofday(2),
//lo que tarda un bucle que incrementa una variable un millón de veces
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int main(){
	struct timeval ini, fin;

	int i=0;
	for(i; i < 1000000; i++);
	
        printf("Hora: %i\n", fin.tv_usec - ini.tv_usec);

        return 0;
}

