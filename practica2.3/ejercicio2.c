//Ej2. Escribir un programa que muestre la política de planificación (como cadena)
//y la prioridad del proceso actual, además de mostrar los valores máximo y mínimo
//de la prioridad para la política de planificación.

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sched.h>

int main(int argc, char **argv){
	int scheduler = sched_getscheduler(getpid());
	if(scheduler == -1){
		perror("Error scheduler");
		return -1;
	}
	
	//Consultar la política de planificación
	switch(scheduler){
		case SCHED_OTHER:
			printf("POLITICA OTHER\n");
			break;
		case SCHED_FIFO:
			printf("POLÍTICA FIFO\n");
			break;
		case SCHED_RR:
			printf("POLÍTICA RR\n");
			break;
		default:
			printf("ERROR\n");
	}

	//Consultar prioridad proceso actual
	struct sched_param prio;
	sched_getparam(getpid(), &prio);
	printf("Prioridad: %d\n", prio.sched_priority);

	//Valores máximo y mínimo de la prioridad para la política
	int max = sched_get_priority_max(scheduler);
	int min = sched_get_priority_min(scheduler);
	printf("Valor máximo: %i\nValor mínimo: %i\n", max, min);

	return 0;
}

