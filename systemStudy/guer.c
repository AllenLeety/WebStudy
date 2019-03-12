#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, const char* argv[])
{
	pid_t pid = fork();
	if(pid == 0)
	{
		sleep(1);
		printf("child, pid = %d, ppid = %d\n", getpid(), getppid());
	}
	else if(pid > 0)
	{
		printf("----parent, pid = %d, ppid = %d\n", getpid(), getppid());
	}
	
	return 0;
}
