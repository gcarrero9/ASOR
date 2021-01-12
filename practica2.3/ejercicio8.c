//Ej8.Usando la versión con execvp(3) del ejercicio7 y la plantilla de demonio del 6, escribir un programa que ejecute cualquier programa como si fuera un demonio.
//Además, redirigir los flujos estándar asociados al terminal usando dup2(2):
//-La salida estándar al fichero /tmp/daemon.out
//-La salida de error estándar al fichero /tmp/daemon.err
//-La entrada estándar a /dev/null
//Comprobar que el proceso sigue en ejecución tras cerrar la shell 

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

	pid_t pid = fork();

	if(pid == -1){
		perror("Error");
		return -1;
	}
	else if(pid == 0){//proceso hijo
		pid_t sid = setsid();
		printf("HIJO. Proceso %i (Padre: %i)\n", getpid(), getppid());

		//Redirigir los flujos estándar asociados al terminal usando dup2(2)
		//la salida estándar al fichero /tmp/daemon.out
		int fd = open("/tmp/daemon.out", O_CREAT | O_RDWR, 00777);
		int fd2 = dup2(fd,2);

		//la salida de error estándar al fichero /tmp/daemon.err
		int fderr = open("/tmp/daemon.err", O_CREAT | O_RDWR, 00777);
		int fderr2 = dup2(fderr, 1);

		//la entrada estándar a /dev/null
		int null = open("/dev/null", O_CREAT | O_RDWR, 00777);
		int null2 = dup2(null, 0);	
	
		if(execvp(argv[1], argv + 1) == -1){
	                printf("Error. No se ha ejecutado correctamente.\n");
			exit(-1);
        	}
				
  	}
	else {
		printf("PADRE. Proceso %i (Padre: %i)\n", getpid(), getppid());
  	}

	return 0;
}

