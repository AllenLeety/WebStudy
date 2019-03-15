#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>

void myfunc(int no)
{
  printf("hello, world\n");
}

int main(int argc, const char* argv[])
{
  struct sigaction act;
  //初始化act
  act.sa_flags = 0;
  sigemptyset(&act.sa_mask);
  act.sa_handler = myfunc;
  sigaction(SIGINT, &act, NULL);

  while(1);

  return 0;
}
