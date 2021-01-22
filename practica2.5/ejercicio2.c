//Ej2.Escribir un servidor UDP de hora

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

	//listen(sd, 16);
	//int cliente_sd = accept(sd, (struct sockaddr *) &cliente_addr, &cliente_len);
	
	while(1){
		ssize_t bytes;
		bytes = recvfrom(sd, buf, 500, 0, (struct sockaddr *) &cliente_addr, &cliente_len);
		buf[1] = '\0';
			
		getnameinfo((struct sockaddr *) &cliente_addr, cliente_len, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
		printf("Bytes %I Conexión desde HOST: %s PUERTO: %s\n", bytes, host, serv);

		time_t tiempo = time(NULL);
		struct tm *tm = localtime(&tiempo);
		size_t max;
		char s[50];

		if(buf[0] == 't'){
			size_t b = strftime(s, max, "%I:%M:%S %p", tm);
			s[b] = '\0';
			sendto(sd, s, b, 0, (struct sockaddr *) &cliente_addr, cliente_len);
		}
		else if(buf[0] == 'd'){
			size_t b = strftime(s, max, "%Y-%m-%d", tm);
			s[b] = '\0';
			sendto(sd, s, b, 0, (struct sockaddr *) &cliente_addr, cliente_len);
		}
		else if(buf[0] == 'q'){
			printf("Exit \n");
			exit(0);
		}
		else{
			printf("No existe %d \n", buf[0]);
		}
	}

	return 0;
}
		
