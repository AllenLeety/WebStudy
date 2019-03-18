#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

int main(int argc, const char* argv[])
{
  //创建一个会话
  //将子进程设置为会长
  pid_t pid = fork();
  if(pid > 0)
  {
    exit(1);
    //kill(getpid(), SIGKILL);
  }
  else if(pid == 0)
  {
    //变成会长
    setsid();
    //让子进程一直活着
    while(1);
  }

  return 0;
}
