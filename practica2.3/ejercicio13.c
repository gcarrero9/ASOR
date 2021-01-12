//Ej13.Escribir un programa que realice el borrado programado del propio ejecutable.
//El programa tendrá como argumento el número de segundos que esperará antes de borrar el fichero.
//El borrado del fichero se podrá detener si se recibe la señal SIGUSR1
//Nota: usar sigsuspend(2) para suspender el proceso y la llamada la sistema apropiada para borrar el fichero.

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

volatile int borrar=0;

void borrado(int s){
	if(s == SIGUSR1)
		borrar=1;
}

int main(int argc, char **argv){
	sigset_t set;
	sigemptyset(&set);
	sigaddset(&set, SIGUSR1);
	sigprocmask(SIG_UNBLOCK, &set, NULL);	

	struct sigaction sa;
	sigaction(SIGUSR1, NULL, &sa);
	sa.sa_handler = borrado;
	sigaction(SIGUSR1, &sa, NULL);

	int segundos = atoi(argv[1]); //atoi para covertir string a int
	int i=0;

	//Bucle con tiempo de espera antes de borrar. Si se recibe (SIGUSR1 entonces borrado=1 y se sale)
	//while(i < segundos && borrado == 0){
//		i++;
//		sleep(1);
//	}

	alarm(segundos);
	sigsuspend(&set);

	if(borrado == 0){
		printf("Se va a proceder a borrar\n");
		unlink(argv[0]); //llamada al sistema para borrar el fichero
	}
	else {
		printf("No se ha borrado porque ha sido interrumpido antes\n");
	}
		
	return 0;
}

