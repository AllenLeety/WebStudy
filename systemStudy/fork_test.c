#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

int main()
{
	int i;
	pid_t pid;
	printf("xxxxxxxxxxxxx\n");

	for(i=0; i<5; i++){
		pid = fork();
		if(pid == 0){
			break;
		}
	}

	if(i < 5){
		sleep(i);
		printf("I am %d child, pid = %u, ppid = %u\n", i+1, getpid(), getppid());
	}else{
		sleep(i);
		printf("I am parent\n");
	}

	return 0;
}
