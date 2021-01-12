//Ej1.TUBERÍA SIN NOMBRE: UNIDIRECCIONAL.
//Escribir un programa que emule el comportamiento de la shell en la ejecución de una sentencia en la forma:
// comando1 argumento1 | comando2 argumento2. El programa creará una tubería sin nombre y creará un hijo:
//-El proceso padre redireccionará la salida estándar al extremo de escritura de la tubería y ejecutará comando1 argumento1
//-El proceso hijo redireccionará la salida estándar al extremo de lectura de la tubería y ejecutará comando2 argumento2
//Probar el funcionamiento con una sentencia similar a:./ejercicio1 echo 12345 wc -c

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char **argv){
	int fd[2];
	pipe(fd); //importante que pipe esté antes que fork
	pid_t pid = fork();
	//fd[0] lectura y fd[1] escritura

	switch(pid){
		case -1:
			perror("fork()");
			return 1;
			break;
		case 0: ///Hijo
			dup2(fd[0], 0);	//Redirecciona la entrada estándar al extremo de la lectura de la tubería
			close(fd[1]);
			close(fd[0]);
			execlp(argv[3], argv[3], argv[4]); //Ejecuta comando2 argumento2
			break;
		default: //Padre
			dup2(fd[1], 1); //Redirecciona la salida estándar al extremo de escritura de la tubería
			close(fd[1]);
			close(fd[0]);
			execlp(argv[1], argv[1], argv[2]); //Ejecuta comando1 argumento1
			break;
	}
	return 0;
}

