#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <stdlib.h>
#include <ctype.h>
#include <arpa/inet.h>
#include <strings.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 6666

int main(void)
{
  int lfd, cfd;
  struct sockaddr_in serv_addr, clie_addr;
  socklen_t clie_addr_len;
  char buf[BUFSIZ], clie_IP[BUFSIZ];//缓冲区
  int n, i, ret;
  
  //创建Socket，指定ipv4协议族，TCP协议
  lfd = socket(AF_INET, SOCK_STREAM, 0);
  if(lfd == -1)
  {
    perror("socket error");
    exit(1);
  }
  //初始化一个地址结构man 7 ip查看对应信息
  bzero(&serv_addr, sizeof(serv_addr)); //将整个结构体清零
  serv_addr.sin_family = AF_INET; //选择协议族为IPv4
  serv_addr.sin_port = htons(SERV_PORT);  //绑定端口号
  serv_addr.sin_addr.s_addr = htonl(INADDR_ANY);  //监听本地所有IP地址

  //绑定服务器地址结构  IP和port
  ret = bind(lfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));
  if(ret == -1)
  {
    perror("bind error");
    exit(1);
  }

  //指定最大同时发起连接数
  ret = listen(lfd, 128); //同一时刻允许向服务器发起连接请求的数量
  if(ret == -1)
  {
    perror("listen error");
    exit(1);
  }

  //阻塞等待客户端发起连接
  clie_addr_len = sizeof(clie_addr);
  //      服务器fd  传出参数客户端   传入传出
  cfd = accept(lfd, (struct sockaddr*)&clie_addr, &clie_addr_len);
  if(cfd == -1)
  {
    perror("accept error");
    exit(1);
  }
  printf("client IP:%s, client port:%d\n",inet_ntop(AF_INET, &clie_addr.sin_addr.s_addr, clie_IP, sizeof(clie_IP)),ntohs(clie_addr.sin_port));

  while(1){
    //读客户端发送来的数据
    n = read(cfd, buf, sizeof(buf));
  
    //处理 小写转大写
    for(i=0; i<n; i++)
      buf[i] = toupper(buf[i]);

    //写回给客户端
    write(cfd, buf, n);
  }

  //关闭
  close(lfd);
  close(cfd);

  return 0;
}
