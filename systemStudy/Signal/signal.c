#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

void myfunc(int no)
{
  printf("catch you signal: %d\n", no);
}

int main(int argc, const char* argv[])
{
  //捕捉ctrl+c
  //注册捕捉函数
  signal(SIGINT, myfunc);

  while(1)
  {
    sleep(1);
printf("hello\n");
  }

  return 0;
}
