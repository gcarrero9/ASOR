//Ej2. TUBERÍA SIN NOMBRE: BIDIRECCIONAL.
//Para la comunicación bi-direccional es necesario crear 2 tuberías, una para cada sentido: p_h y h_p.
//Escribir un programa que implemente el mecanismo de sincronización de parada y espera:
//-El padre leerá de la entrada estándar (terminal) y enviará el mensaje al proceso hijo, escribiéndolo en la tubería p_h.
//Entonces permanecerá bloqueado esperando la confirmación por parte del hijo en la otra tubería, h_p
//-El hijo leerá de la tubería p_h, escribirá el mensaje por la salida estándar y esperará 1 segundo.
//Entonces enviará el carácter 'l' al proceso padre, escribiéndolo en la tubería h_p, para indicar que está listo.
//Después de 10 mensajes enviará el caracter 'q' para indicar al padre que finalice.

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>
#include <unistd.h>

int main(int argc, char **argv){
	int p_h[2];
	int h_p[2];

	pipe(p_h); //importante que la tubería se cree antes que el fork
	pipe(h_p);

	pid_t pid = fork();

	switch(pid){
		case -1:
			perror("fork()");
			return 1;
			break;
		case 0: ///Hijo
			close(p_h[1]);
			close(p_h[0]);
			int i=0;
			for(i; i < 10; i++){
				char buf[100];
				int bytes = read(p_h[0], buf, 99);
				buf[bytes] = '\0';
				printf(" [HIJO] Mensaje: %s\n", buf);
				sleep(1);
				if(i != 9)
					write(h_p[1], "l", 1);			
			}
			write(h_p[1], "q", 1);
			break;
		default: //Padre
			close(p_h[1]);
			close(h_p[0]);
			char stop;
			char buf[100];
			do{
				printf("[PADRE] Mensaje: %s\n");
				int bytes = read(0, buf, 99);
				buf[bytes] = '\0';
				write(p_h[1], buf, 99);
				read(h_p[0], &stop, 1); 
			}while(stop != 'q');
			//wait(NULL);
			printf("10 mensajes enviados con éxito. \n");
			break;
	}
	return 0;
}

