//Ej5. MULTIPLEXACION SÍNCRONA DE ENTRADA/SALIDA
//Crear otra tubería con nombre. Escribir un programa que espere hasta que haya datos listos para leer en alguna de ellas.
//El programa debe mostrar la tubería desde la que leyó y los datos leídos. Consideraciones:
//-Para optimizar las operaciones de lectura usar un buffer (ej. de 256 bytes).
//-Usar read(2) para leer de la tubería y gestionar adecuadamente la longitud de los datos leídos.
//-Normalmente, la apertura de la tubería para lectura se bloqueará hasta que se abra para escritura (ej con echo 1 mayor tubería). Para evitarlo, usar la opción O_NONBLOCK en open(2)
//-Cuando el escritor termina y cierra la tubería, read(2) devolverá 0, indicando el fin de fichero, por lo que hay que cerrar la tubería y volver a abrirla.
//si no, select(2) considerará el descriptor siempre listo para lectura y no se bloqueará.

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

	char *tub1 = "tuberia1";
	char *tub2 = "tuberia2";

	char buffer[256];
	mkfifo(tub1, 0644);
	mkfifo(tub2, 0644);

	int fd1 = open(tub1, O_RDONLY | O_NONBLOCK);
	int fd2 = open(tub2, O_RDONLY | O_NONBLOCK);

	int result, fdactual;
	
	while(result != -1){
		fd_set set;
		FD_ZERO(&set);
		FD_SET(fd1, &set);
		FD_SET(fd2, &set);
		
		result = select((fd1 < fd2) ? fd2 + 1: fd1 + 1, &set, 0, 0, 0);
		if(result > 0){
			if(FD_ISSET(fd1, &set)){
				fdactual = 1;
				fdactual = fd1;
			}
			else if(FD_ISSET(fd2, &set)){
				fdactual = 2;
				fdactual = fd2;
			}
		ssize_t readsize = 256;
			while (readsize == 256){
				readsize = read(fdactual, buffer, 256);
				buffer[readsize] = '\0';
				printf("Tuberia %i: %s", fdactual, buffer);
			}
			if(readsize != 256 && fdactual == 1){
				close(fd1);
				fd1 = open(tub1, O_RDONLY | O_NONBLOCK);
				if(fd1 == -1){
					perror("No se puede abrir la segunda tubería\n");
					close(fd1);
					close(fd2);
					return -1;
				}
			}
			else if(readsize != 256 && fdactual == 2){
				close(fd2);
				fd2 = open(tub2, O_RDONLY | O_NONBLOCK);
				if(fd2 == -1){
					perror("No se puede abrir la segunda tubería\n");
					close(fd1);
					close(fd2);
					return -1;
				}
			}
		}
	}//while

	close(fd1);
	close(fd2);

	return 0;
}

