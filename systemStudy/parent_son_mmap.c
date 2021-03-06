#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <sys/wait.h>

int main(int argc, const char* argv[])
{
  //打开一个文件
  int fd = open("english.txt", O_RDWR);
  int len = lseek(fd, 0, SEEK_END);

  //创建内存映射区
  void *ptr = mmap(NULL, len, PROT_READ | PROT_WRITE, MAP_SHARED, fd, 0);
  if(ptr == MAP_FAILED)
  {
    perror("mmap error");
    exit(1);
  }

 // printf("%s", (char*)ptr);

  pid_t pid = fork();
  if(pid == -1)
  {
    printf("fork error");
    exit(1);
  }
  if(pid > 0)
  {
    //写数据
    strcpy((char*)ptr, "你是谁？你在哪？");
    //回收
    wait(NULL);
  }
  else if(pid == 0)
  {
    //读数据
    printf("%s\n", (char*)ptr);
  }

  //释放内存映射区
  int ret = munmap(ptr, len);
  if(ret == -1)
  {
    perror("munmap error");
    exit(1);
  }
  close(fd);

  return 0;
}
