/Ej1. Escribir un programa que obtenga todas las posibles direcciones con las que se podría crear un s$
//Para cada dirección, mostrar la IP numérica, la familia de protocolos y tipo de socket. Comprobar el $
//-Una dirección IPv4 válida
//-Una dirección IPv6 válida
//-Un nombre de dominio válido
//-Un nombre en /etc/hosts válido
//-Una dirección o nombre incorrectos en cualquiera de los casos anteriores

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>


int main(int argc, char **argv){
        struct addrinfo filtro; //para seleccionar el tipo de direcciones que quiero
        struct addrinfo *resultado;

        memset(&filtro, 0, sizeof(struct addrinfo)); //Inicializar la estructura y poner todo a cero

        filtro.ai_family = AF_UNSPEC; //IPv4 y IPv6
        filtro.ai_flags = AI_PASSIVE;
        filtro.ai_socktype = 0; //Cualquier protocolo

	int rc = getaddrinfo(argv[1], argv[2], &filtro, &resultado);
        if(rc != 0){
                printf("[ERROR] getaddrinfo: %s\n", gai_strerror(rc));
                return -1;
        }

	struct addrinfo *i;
        for(i = resultado; i != NULL; i->ai_next){
                char host[NI_MAXHOST];
                char serv[NI_MAXSERV];
                getnameinfo(i->ai_addr, i->ai_addrlen, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHO$
                printf("HOST: %s PUERTO: %s\n", host, serv);
        }

	freeaddrinfo(resultado); //liberamos la memoria de la lista

        return 0;
}
