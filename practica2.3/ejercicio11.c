//Ej11.Escribir un programa que bloquee las señales SIGINT y SIGTSTP. Después de bloquearlas el programa debe suspender su ejecución con sleep(3)
//un número de segundos que se obtendrán de la variable de entorno SLEEP_SECS.
//Después de despertar de sleep(3), el proceso debe informar de si recibió la señal SIGINT y/o SIGTSTP.
//En este último caso, debe desbloquearla con lo que el proceso se detendrá y podrá ser reanudad en la shell.

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

int main(int argc, char **argv){
	sigset_t blk_set;

	//Inicializa set al conjunto vacío
	sigemptyset(&blk_set);
	//Añadir las señales SIGINT y SIGTSTP a SET
	sigaddset(&blk_set, SIGINT);
	sigaddset(&blk_set, SIGTSTP);
	
	//Establecer bloqueo
	sigprocmask(SIG_BLOCK, &blk_set, NULL); 
	
	//Código protegido

	//Para suspender la ejecución obtenemos primero los segundos de la variable de entorno SLEEP_SECS
	char *sleep_secs = getenv("SLEEP_SECS");
	int segundos = atoi(sleep_secs);
	printf("Se va a suspender el proceso durante %d segundos\n", segundos);
	//Suspender la ejecución
	sleep(segundos);
	
	//Después de despertar, informar si recibió SIGINT y/o SIGTSTP
	sigset_t signalpending;
	sigpending(&signalpending);

	if(sigismember(&signalpending, SIGINT) == 1){
		printf("Se ha recibido SIGINT\n");
		sigdelset(&blk_set, SIGINT);
	}
	else {
		printf("No se ha recibido SIGINT\n");
	}
	if(sigismember(&signalpending, SIGTSTP) == 1){
		printf("Se ha recibido SIGTSTP\n");
		sigdelset(&blk_set, SIGTSTP);
	}
	else {
		printf("No se ha recibido SIGTSTP\n");
	}

	//Desbloqueo
	sigprocmask(SIG_UNBLOCK, &blk_set, NULL);

	printf("El comando terminó de ejecutarse\n");
	return 0;
}

