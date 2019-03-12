/*************************************************************************
	> File Name: look_fork.c
	> Author: ma6174
	> Mail: ma6174@163.com 
	> Created Time: 2019年03月11日 星期一 15时21分51秒
 ************************************************************************/
#include <stdio.h>
#include <unistd.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int counter=200;
int main(int argc, const char* argv[])
{
	int i=0;
	int number = 3;
	pid_t pid;

	for(i=0; i<number; ++i)
	{
		pid = fork();
		if(pid == 0)//只得到兄弟子进程
		{
			break;
		}
	}
	
	//如果判断是第几个孩子
	//通过循环因子i去判断
	//first
	if(i == 0)
	{
		counter +=200;
		printf("first process, pid = %d\n", getpid());
		printf("--counter = %d\n", counter);
	}
	//second
	if(i == 1)
	{
		counter =+200;
		printf("second process, pid = %d\n", getpid());
		printf("--counter = %d\n", counter);
	}
	//third
 	if(i == 2)
	{
		counter +=200;
		printf("third process, pid = %d\n", getpid());
		printf("--counter = %d\n", counter);
	}
	//parent
	if(i == 3)
	{
		counter +=400;
		printf("parent process, pid = %d\n", getpid());
		printf("--counter =%d\n", counter);
	}

	return 0;
}
