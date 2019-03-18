#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <pthread.h>  //线程对应的头文件

int count = 0;
void* myfunc(void* arg)
{
  //取数据
  int num = (int)arg;
  //打印子线程的id
  printf("%dth child thread id: %lu\n", num, pthread_self());

  for(int i=0; i<5; i++)
  {
    printf("%dth child i = %d\n", num, i);
    if(i == 2)
    {
      //子线程退出
      pthread_exit(&count);
    }
  }
  return NULL;
}

int main(int argc, const char* argv[])
{
  //创建一个子线程
  //线程ID变量
  pthread_t pthid[5];
  for(int i=0; i<5; i++)
  { 
    //第4个人参数传递的是地址
    // pthread_create(&pthid[i], NULL, myfunc, (void*)&i);
    //传值
    int ret = pthread_create(&pthid[i], NULL, myfunc, (void*)i);
    if(ret != 0)
    {
      printf("%s\n", strerror(ret));
    }
    count = i;
  }
  printf("parent thread id: %lu\n", pthread_self());

  //退出主线程
  // pthread_exit(NULL);
  // 阻塞等待子线程退出，并且回收其pcb
  void* ptr = NULL;
  pthread_join(pthid, &ptr);
  printf("number = %d\n", *(int*)ptr);

  int i=0;
  while(i<10)
  {
    printf("parent i = %d\n", i++);
  }
  


  return 0;
}
