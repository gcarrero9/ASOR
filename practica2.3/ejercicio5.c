//Ej5. Escribir un programa que muestre los identificadores del proceso:
//Identificador de proceso, de proceso padre, de grupo de procesos y de sesión.
//Mostrar además el número máximo de ficheros que puede abrir el proceso y el directorio de trabajo actual.

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int main(int argc, char* argv[]){
	
	printf("PID: %i\n", getpid()); //mostrar el id del proceso
	printf("PPID: %i\n", getppid()); //mostrar el id del proceso padre
	printf("PGID: %i\n", getpgid(getpid())); //Grupo de procesos.
	printf("PSID: %i\n", getsid(getpid())); //Obtener el identificador de la sesión
	
	//Mostrar además el número máximo de ficheros que puede abrir el proceso.
	struct rlimit fich;
	if(getrlimit(RLIMIT_NOFILE, &fich) == -1) { //Obtener el limite de un proceso.
        	perror("Error, no se puede obtener el límite");
		return -1;
	}
	printf("Número máximo de ficheros %i\n", fich.rlim_max);

	//Directorio de trabajo actual
	char buf[100];
	if(getcwd(buf, 100) == NULL){
		perror("Error al consultar el directorio de trabajo actual");
		return -1;
	}
	printf("Directorio de trabajo actual: %s\n", buf);

	return 0;
}

