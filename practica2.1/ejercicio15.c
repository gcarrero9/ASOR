//Ej15. Modificar programa anterior para que muestre la hora legible, usando strftime(3)
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <locale.h>


int main(){
	struct tm* anno;
	time_t t = time(NULL);

	anno = localtime(&t);
	
        printf("ANNO: %d\n", 1900 + anno->tm_year);

	setlocale(LC_ALL, "es_ES");

	char buf[100];
	strftime(buf, 100, "%A, %H:%M", anno);
	printf("Hoy es %s\n", buf);

        return 0;
}

