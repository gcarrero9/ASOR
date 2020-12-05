//Escribir un programa que muestre, igual que id, el UID real y efectivo del usuario.
//¿Cuando podríamos asegurar que el fichero del programa tiene activado el bit setuid?
//Cuando el uid real y el efectivo no coincidan.

#include <sys/types.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>

int main(){
	
	printf(" UID Real %i\n UID Efectivo %i\n", getuid(), geteuid());
	return 0;
}

