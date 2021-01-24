//Ej.6 Crear un servidor TCP de eco que escuche por conexiones entrantes en una dirección (IPv4 o IPv6) y puerto dados. 
//Cuando reciba una conexión entrante, debe mostrar la dirección y número de puerto del cliente. 
//A partir de ese momento, enviará al cliente todo lo que reciba desde el mismo (eco). 
//Comprobar su funcionamiento empleando la herramienta Netcat como cliente. 
//Comprobar qué sucede si varios clientes intentan conectar al mismo tiempo.

#include <sys/types.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/socket.h>
#include <netdb.h>
#include <errno.h>
#include <string.h>

void haz_conexion(int cliente_sd){
	char buffer[80];
	
	while(1){
		int bytes = recv(cliente_sd, buffer, 79, 0); //se usa cliente_sd porque ya no queremos recibir datos de cualquier cliente sino del que hemos recibido la conexión
		if(bytes == 0){
			printf("\t Fin de la conexión\n");
			close(cliente_sd);
			break;
		}
	
		buffer[bytes] = '\0';
		printf("\tMensjae: %s\n", buffer);
		send(cliente_sd, buffer, bytes, 0);
	}
}

int main(int argc, char **argv)	{
	char buffer[80];
	
	// INICIALIZACION DEL SOCKET
	
	struct addrinfo filtro; //para seleccionar el tipo de direcciones que quiero
	struct addrinfo *resultado;

	memset(&filtro, 0, sizeof(struct addrinfo)); //para inicializar la estructura y poner todo a 0
	
	filtro.ai_flags = AI_PASSIVE; //Direccion sin identificar
	filtro.ai_family = AF_UNSPEC; //tanto IPV4 como IPV6
	filtro.ai_socktype = SOCK_STREAM; //tcp

	//argv[1] = host argv[2] = puerto. addrinfo es un puntero doble.
	int rc = getaddrinfo(argv[1], argv[2], &filtro, &resultado);
	
	if(rc != 0){
		printf("[ERROR] getaddrinfo: %s\n", gai_strerror(rc));
		return -1;
	}

	int sd = socket(resultado->ai_family, resultado->ai_socktype, 0);
	bind(sd, resultado->ai_addr, resultado->ai_addrlen);
	freeaddrinfo(resultado);

	// FIN DE INICIALIZACIÓN

	// GESTIÓN DE LA CONEXIÓN
	
	listen(sd, 16); //minimo 16.
	while(1){
		char host[NI_MAXHOST];
		char serv[NI_MAXSERV];
		struct sockaddr_storage cliente_addr;
		socklen_t cliente_len = sizeof(struct sockaddr_storage);

		int cliente_sd = accept(sd, (struct sockaddr *) &cliente_addr, &cliente_len); //Cada conexión se gestiona a través del accept. Esto no pasaba en UDP, que era con recvfrom.
		
		//esto es genérico	
		getnameinfo((struct sockaddr *) &cliente_addr, cliente_len, host, NI_MAXHOST, serv, NI_MAXSERV, NI_NUMERICHOST | NI_NUMERICSERV);
		printf("Conexión desde HOST: %s PUERTO: %s\n", host, serv);

		// TRATAR LA CONEXIÓN
		haz_conexion(cliente_sd);
	}
	return 0;
}
