#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#define SERV_IP "127.0.0.1"
#define SERV_PORT 6666

int main(void)
{
  int cfd;
  struct sockaddr_in serv_addr;//服务器端addr
//  socklen_t serv_addr_len;
  char buf[BUFSIZ];
  int n;

  //建立socket
  cfd = socket(AF_INET, SOCK_STREAM, 0);
  
  memset(&serv_addr, 0, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(SERV_PORT);
  inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);

  //发起连接
  connect(cfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

  while(1){
    //写
    //输入hello world--->fgets函数--->"hello world\n\0"
    fgets(buf, sizeof(buf), stdin);
    write(cfd, buf, strlen(buf));
    //读
    n = read(cfd, buf, sizeof(buf));
    write(STDOUT_FILENO, buf, n);
  }

  //关闭
  close(cfd);

  return 0;
}
