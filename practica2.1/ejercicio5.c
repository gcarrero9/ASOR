#include <sys/utsname.h>
#include <stdio.h>
#include <stdlib.h>

int main(int argc, char **argv)
{
	struct utsname buf;
	
	int error;
	error = uname(&buf);
	
	if(error == -1){
		perror("Error uname");
		return -1;
	}
	printf("SYSNAME: %s\n", buf.sysname);
	printf("VERSION: %s\n", buf.version);
	printf("HOST: %s\n", buf.nodename);
	printf("RELEASE: %s\n", buf.release);
	printf("HARDWARE: %s\n", buf.machine);
	return 0;
}

