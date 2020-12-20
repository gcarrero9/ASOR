//Ej 9. Escribir un programa que emule el comportamiento de stat y muestre:
//-Número major y minor asociado al dispositivo
//-El número de i-nodo del fichero
//-El tipo de fichero(directorio, enlace simbólico o fichero ordinario)
//-La hora en la que se accedió el fichero por última vez (acceso: time_t st_atime)
//-¿Qué diferencia hay entre st_mtime y st_ctime?
//-time_t st_mtime: Última modificación del fichero.
//-time_t st_ctime: Último cambio de estado.

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <time.h>

int main(int argc, char* argv[]){
	struct stat estado;

	if(stat(argv[1], &estado) == -1){
		perror("error");
		return -1;
	}

	printf("Número major: %li\n", major(estado.st_dev));
	printf("Número minor: %li\n", minor(estado.st_dev));
	printf("Número de i-nodo: %li\n", estado.st_ino);
	printf("Tipo de fichero: %i\n", estado.st_mode);
		mode_t modo = estado.st_mode;
	if(S_ISLNK(modo)){
		printf("Enlace simbólico\n", argv[1]);
	}
	if(S_ISREG(modo)){
		printf("Fichero normal\n", argv[1]);
        }	
	if(S_ISDIR(modo)){
		printf("Directorio\n", argv[1]);
        }	

	time_t h = estado.st_atime;
	struct tm *hora = localtime(&h);
	
	printf("Hora último acceso: %d:%d\n", hora->tm_hour, hora->tm_min);
	
	return 1;
}

