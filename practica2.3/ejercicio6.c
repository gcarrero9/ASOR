//Ej6. Escribir una plantilla de demonio (creación del nuevo proceso y de la sesión)
//en el que únicamente se muestren los atributos del proceso (como en el ejercicio anterior).
//Además, fijar el directorio de trabajo del dominio a /tmp

//¿Qué sucede si el proceso padre termina antes que el hijo (observar el PPID del proceso hijo)?
//¿Y si el proceso que termina antes es el hijo (observar el estado del proceso hijo con ps)?

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <unistd.h>
#include <sys/time.h>
#include <sys/resource.h>

int atributos(void){
	printf("Proceso HIJO \n");
	printf("PID: %i\n", getpid()); //mostrar el id del proceso
	printf("PPID: %i\n", getppid()); //mostrar el id del proceso padre
	printf("PGID: %i\n", getpgid(getpid())); //Grupo de procesos.
	printf("PSID: %i\n", getsid(getpid())); //Obtener el identificador de la sesión
	
	//Mostrar además el número máximo de ficheros que puede abrir el proceso.
	struct rlimit fich;
	if(getrlimit(RLIMIT_NOFILE, &fich) == -1) { //Obtener el limite de un proceso.
        	perror("Error, no se puede obtener el límite");
		return -1;
	}
	printf("Número máximo de ficheros %i\n", fich.rlim_max);

	//Directorio de trabajo actual
	char buf[100];
	if(getcwd(buf, 100) == NULL){
		perror("Error al consultar el directorio de trabajo actual");
		return -1;
	}
	printf("Directorio de trabajo actual: %s\n", buf);

	return 0;
}

int main(int argc, char* argv[]){
	//Tanto el proceso como la sesión se puede crear como pid_t o como int.
	pid_t pid = fork(); //Crear proceso
	if(pid == -1){
		perror("Error");
		return -1;
	}
	else if(pid == 0){//proceso hijo
		if(chdir("/tmp") == -1){ //Cambiar de directorio actual
			perror("Error al querer cambiar de directorio actual");
			return -1;	
		}
		//Creación de la sesión
		pid_t sid = setsid();
		if(sid == -1){
			perror("Error, no se ha podido crear nueva sesión");
			return -1;
		}
		if(atributos() == -1){
			perror("Error atributos");
			return -1;
		}

	}
	else {
		printf("Proceso PADRE: %i\n", getpid());
		sleep(3);
		return 0;
	}

}

