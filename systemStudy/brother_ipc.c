#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>

int main(int argc, const char* argv[])
{
  int fd[2];
  int ret = pipe(fd);
  if(ret == -1)
  {
    perror("pipe error");
    exit(1);
  }
  
  int i=0;
  for(i=0; i<2; i++)
  {
    pid_t pid = fork();
    if(pid == 0)
    {
      break;
    }
  }

  //子进程1
  //ps aux
  if(i == 0)
  {
    //写管道的操作，关闭读端
    close(fd[0]);
    //文件描述符重定向
    //stdout_fileno --> 管道的写端
    dup2(fd[1], STDOUT_FILENO);
    //执行ps aux
    execlp("ps", "ps", "aux", NULL);
  }
  //子进程2
  //prep "bash"
  else if(i == 1)
  {
    //读管道的操作，关闭写端
    close(fd[1]);
    //文件描述符重定向
    //stdin_fileno --> 管道的读端
    dup2(fd[0], STDIN_FILENO);
    //执行 grep bash
    execlp("grep", "grep", "bash", NULL);
  }
  else if(i == 2)//父进程
  {
    close(fd[0]);
    close(fd[1]);
    //回收子进程
    pid_t wpid;
    while((wpid = waitpid(-1, NULL, WNOHANG)) != -1)
    {
      if(wpid == 0)
      {
        continue;
      }
      printf("child died pid = %d\n", wpid);
    }
  }

  printf("pipe[0] = %d\n", fd[0]);
  printf("pipe[1] = %d\n", fd[0]);
  
  return 0;
}
