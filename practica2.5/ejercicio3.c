//Ej3. Escribir el cliente para el servidor de hora. El cliente recibirá como argumentos la dirección del servidor, el puerto del servidor y el comando-

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <time.h>
#include <arpa/inet.h>
#include <netinet/in.h>

int main(int argc, char **argv){

	/* INICIALIZACION DEL SOCKET */

	struct addrinfo filtro;
	struct addrinfo *resultado;
	
	memset(&filtro, 0, sizeof(struct addrinfo));
	filtro.ai_flags = AI_PASSIVE;
	filtro.ai_family = AF_UNSPEC;
	filtro.ai_socktype = SOCK_DGRAM;

	int rc = getaddrinfo(argv[1], argv[2], &filtro, &resultado);
	if(rc != 0){
		printf("[ERROR] getaddrinfo: %s\n", gai_strerror(rc));
		return -1;
	}

	int sd = socket(resultado->ai_family, resultado->ai_socktype, 0);
	if(bind(sd, resultado->ai_addr, resultado->ai_addrlen) != 0){
		printf("[ERROR] \n");
		return -1;
	}
	freeaddrinfo(resultado);

	/* FIN DE INICIALIZACIÓN */

	/* GESTION DE LA CONEXION */

	char host[NI_MAXHOST];
	char serv[NI_MAXSERV];
	char buf[500];

	struct sockaddr_storage cliente_addr;	
	socklen_t cliente_len = sizeof(cliente_addr);

	printf("%s\n", argv[3]);
	
	if(*argv[3] == 't'){
		char s[50];
		ssize_t bytes = recvfrom(sd, s, 50, 0, (struct sockaddr *) &cliente_addr, &cliente_len);
		s[bytes] = '\0';
		printf("%s\n", s);
	}

	return 0;
}
