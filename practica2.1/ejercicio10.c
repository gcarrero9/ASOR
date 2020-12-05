//Muestra ademas el nombre de usuario, el directorio home y descripcion del usuario

#include <sys/types.h>
#include <sys/utsname.h>
#include <unistd.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <pwd.h>
int main(){
	uid_t uid = getuid();
	struct passwd *info = getpwuid(uid);
	
	printf(" UID Real %i\n UID Efectivo %i\n", getuid(), geteuid());
	char *nombre = info->pw_name;
	printf("NOMBRE USUARIO: %s\n", nombre);
	char *des = info->pw_gecos;
	printf("DESCRIPCIÓN: %s\n", des);
	char *home = info->pw_dir;
	printf("DIRECTORIO HOME: %s\n", home);	
	
	return 0;
}
