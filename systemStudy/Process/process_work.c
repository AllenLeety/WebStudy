#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <string.h>
#include <signal.h>
#include <sys/time.h>
#include <time.h>
#include <fcntl.h>

void dowork(int no)
{
  time_t curtime;
  //得到当前系统的时间
  time(&curtime);
  //格式化时间
  char* pt = ctime(&curtime);
  //将时间写入文件
  int fd = open("/home/allen/WebStudy/systemStudy/Process/temp.txt", O_CREAT | O_WRONLY | O_APPEND, 0664);
  write(fd, pt, strlen(pt)+1);
  close(fd);
}

int main(int argc, const char* argv[])
{
  pid_t pid = fork();
  if(pid > 0)
  {
    //父进程退出
    exit(1);
  }
  else if(pid == 0)
  {
    //变成会长
    setsid();
    //改变进程的个工作目录
    chdir("/home/allen/WebStudy/systemStudy/Process/process1");
    //重置文件掩码
    umask(0);
    //关闭文件描述符
    close(STDIN_FILENO);
    close(STDOUT_FILENO);
    close(STDERR_FILENO);
    //执行核心工作
    //注册信号捕捉
    struct sigaction act;
    act.sa_flags = 0;
    act.sa_handler = dowork;
    sigemptyset(&act.sa_mask);
    sigaction(SIGALRM, &act, NULL);
    //创建定时器
    struct itimerval val;
    //第一次触发的时间
    val.it_value.tv_usec = 0;
    val.it_value.tv_sec = 2;
    //循环周期
    val.it_interval.tv_usec = 0;
    val.it_interval.tv_sec = 2;
    setitimer(ITIMER_REAL, &val, NULL);
    //保证子进程处于运行状态
    while(1);
  }

  return 0;
}
