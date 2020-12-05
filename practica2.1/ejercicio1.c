#include <stdio.h>
#include <errno.h>
#include <string.h>

int main()
{
	if(setuid(0) == -1){
		perror("error");
	}
	return 1;
}

