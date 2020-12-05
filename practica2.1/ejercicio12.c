//Ej12: Escribir un programa que muestre la hora en segundos desde time(2)
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int main(){
	time_t hora = time(NULL);

	if(hora == -1){
		printf("Error %s\n", errno, strerror(errno));
	}
	
        printf("Hora: %i\n", hora);

        return 0;
}
