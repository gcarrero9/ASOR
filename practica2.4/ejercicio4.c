//Ej4. TUBERÍA CON NOMBRE
//Escribir un programa que abra la tubería con el nombre anterior en modo sólo escritura, y escriba en ella el primer argumento del programa.
//En otro terminal, leer de la tubería usando un comando adecuado.

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <string.h>

int main(int argc, char **argv){
	char *TUBERIA = getenv("TUBERIA");
	char *tub = strcat(TUBERIA, "/tub");

	printf("TUBERIA: %s\n", tub);

	mkfifo(tub, 0777); //abrir tubería

	int fd = open(tub, O_WRONLY);

	write(fd, argv[1], strlen(argv[1])); //escribir en la tubería el primer argumento del programa

 	close(fd);

	return 0;
}

