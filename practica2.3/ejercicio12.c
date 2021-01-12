//Ej12.Escribir un programa que instale un manejador sencillo para las señales SIGINT y SIGTSTP.
//El manejador debe contar las veces que ha recibido cada señal. El programa principal permanecerá en bucle que se detendrá cuando se haya recibido 10 señales.
//El número de señales de cada tipo se mostrará al finalizar el programa.

#include <stdio.h>
#include <errno.h>
#include <stdlib.h>
#include <signal.h>

static volatile int cont_int =0;
static volatile int cont_tstp = 0;

void contar(int s){
	if(s == SIGINT)
		cont_int++;
	if(s == SIGTSTP)
		cont_tstp++;
}

int main(int argc, char **argv){
	struct sigaction sa;
	
	sigaction(SIGINT, NULL, &sa);
	sa.sa_handler = contar;
	sigaction(SIGINT, &sa, NULL);

	sigaction(SIGTSTP, NULL, &sa);
	sa.sa_handler = contar;
	sigaction(SIGTSTP, &sa, NULL);	

	sigset_t set;
		sigemptyset(&set);
		while(cont_int + cont_tstp < 10)
			sigsuspend(&set);

	
	printf("SIGINT capturado: %i\n", cont_int);
	printf("SIGTSTP capturado: %i\n", cont_tstp);
		
	return 0;
}

