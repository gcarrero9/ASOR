//Ej14. Función que muestre el año usando la funcion localtime(3)
#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>

int main(){
	struct tm* anno;
	time_t t = time(NULL);

	anno = localtime(&t);
	
        printf("ANNO: %d\n", 1900 + anno->tm_year);

        return 0;
}

