//Ej 11. Escribir un programa que reciba una ruta a un fichero como argumento. Con link(2) y symlink(2)
//Si la ruta es un fichero regular, creará un enlace simbólico y rígido con el mismo nombre terminado en .sym y .hard respectivamente.
//comprobar el resultado con la orden ls.
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

int main(int argc, char* argv[]){
	struct stat estado;

	if(stat(argv[1], &estado) == -1){
		perror("error");
		return -1;
	}

	char * rigido = malloc(sizeof(char)*(5 + strlen(argv[1])));
	char * simb = malloc(sizeof(char)*(5 + strlen(argv[1])));

	//strcpy(rigido, argv[1]);
	//rigido=strcat(rigido, ".rigido");
	//strcpy(simb, argv[1]);
	//simb=strcat(simb, ".simb");

	mode_t modo = estado.st_mode;

	if(S_ISREG(modo)){
		if(link(argv[1],rigido) == -1){
			printf("Error enlace rigido\n");
		}
		else{
			printf("Se ha creado enlace rigido\n");
		}
		if(symlink(argv[1], simb) == -1){
			printf("Error enlace simbolico\n");
		}
		else {
			printf("Se ha creado enlace simbolico\n");
		}
	}
	else {
		printf("No es un fichero normal");
	}

	return 1;
}

