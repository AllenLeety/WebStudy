#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/wait.h>

int main(int argc, const char* argv[])
{
	pid_t pid = fork();
	//父进程
	if(pid > 0)
	{
		printf("parent process, pid = %d, ppid = %d\n", getpid(), getppid());
		//回收子进程
		int status;
    pid_t wpid = wait(&status);
    //判断是否正常退出
    if(WIFEXITED(status))
    {
      printf("exit value: %d\n", WEXITSTATUS(status));
    }
    //是否被信号杀死
    if(WIFSIGNALED(status))
    {
      printf("exit by signal: %d\n", WTERMSIG(status));
    }
		printf("died child pid = %d\n", wpid);
		
	}
	//子进程
	else if(pid == 0)
	{
		sleep(2);
		printf("child process, pid = %d, ppid = %d\n", getpid(), getppid());
	}

	for(int i=0; i<5; i++)
	{
		printf("i = %d\n", i);
	}

	return 9;
  // exit(12);
}
