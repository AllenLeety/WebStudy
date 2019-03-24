#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <arpa/inet.h>
#include <pthread.h>
#include <ctype.h>
#include <fcntl.h>

#include "wrap.h"

#define MAXLINE 8192
#define SERV_PORT 8000

struct s_info{    //定义一个结构体，将地址结构跟cfd捆绑
  struct sockaddr_in clie_addr;
  int cfd;
};

void *do_work(void *arg)
{
  int n, i;
  struct s_info *ts = (struct s_info*)arg;
  char buf[MAXLINE];
  char str[INET_ADDRSTRLEN];  //#define INET_ADDRSTRLEN 16 可用"[+d"查看

  while(1)
  {
    n = Read(ts->cfd, buf, MAXLINE);  //读客户端
    if(n == 0){
      printf("the client %d closed...\n", ts->cfd);
      break;  //跳出循环，关闭close
    }
    printf("reciverd from %s at PORT %d\n",
        inet_ntop(AF_INET, &(*ts).clie_addr.sin_addr, str, sizeof(str)),
        ntohs((*ts).clie_addr.sin_port)); //打印客户端信息 IP port

    for(i=0; i<n; i++)
      buf[i] = toupper(buf[i]); //小写转大写
    Write(STDOUT_FILENO, buf, n); //写出至屏幕
    Write(ts->cfd, buf, n); //回写给客户端
  }
  Close(ts->cfd);

  return (void*)0;
}

int main(void)
{
  int cfd, lfd;
  struct sockaddr_in serv_addr, clie_addr;
  socklen_t clieaddr_len;
  pthread_t thid;
  struct s_info ts[256];  //根据最大线程数创建结构体数组
  int i = 0;

  lfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&serv_addr, sizeof(serv_addr)); //创建一个socket，得到lfd
  serv_addr.sin_family = AF_INET; //地址结构清零
  serv_addr.sin_port = htons(SERV_PORT);  //指定端口号8000
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //指定本地任意IP
  Bind(lfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr)); //绑定

  Listen(lfd, 128); //设置同一时刻连接服务器上限数

  printf("Accepting client connect...\n");

  while(1){
    clieaddr_len = sizeof(clie_addr);
    //阻塞监听客户端连接请求
    cfd = Accept(lfd, (struct sockaddr *)&clie_addr, &clieaddr_len);
    ts[i].clie_addr = clie_addr;
    ts[i].cfd = cfd;

    /*达到线程最大数时，pthread_create出错处理，增加服务器稳定性*/
    pthread_create(&thid, NULL, do_work, (void*)&ts[i]);
    pthread_detach(thid); //子线程分离，防止僵尸线程产生
    i++;
  }

  return 0;
}
