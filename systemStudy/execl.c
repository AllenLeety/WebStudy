#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, const char* argv[])
{
	//父进程数数
	for(int i=0; i<8; i++)
	{
		printf("parent i = %d\n", i);
	}

	//创建一个子进程
	pid_t pid = fork();
	
	//让子进程执行ls命令
	if(pid == 0)
	{
		//ls程序使用的子进程的地址空间
		//execl("/home/Webstudy/systemStudy/fork","fork", NULL);
		
		 execlp("ps", "ps", "aux", NULL);
		perror("execlp");
		exit(1);
	}
	
	for(int i=0; i<8; i++)
	{
		printf("++++ i = %d\n", i);
	}

	return 0;
}
