#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>

int main(int argc, const char* argv[])
{
  //设置定时器
  alarm(1);
  int i=0;
  while(1)
  {
    printf("%d \n", i++);
  }

  return 0;
}
