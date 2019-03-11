/*************************************************************************
	> File Name: fork.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2019年03月11日 星期一 11时20分07秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<string.h>

int main(int argc, char* argv[])
{
	pid_t pid;

	for(int i=0; i<4; i++)
	{
		printf("------i=%d\n", i);
	}
	pid = fork();
	//父进程
	if(pid>0)
	{
		printf("parent process,pid=%d\n", getpid());
	}
	//子进程
	else if(pid==0){
		printf("child process, pid=%d, ppid=%d\n", getpid(), getppid());
	}

	for(int i=0; i<4; i++){
		printf("i=%d\n", i);
	}

	return 0;
}
