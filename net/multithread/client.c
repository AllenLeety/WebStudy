#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#include "wrap.h"

#define MAXLINE 80
#define SERV_PORT 8000

int main(void)
{
  int cfd;
  struct sockaddr_in serv_addr;
  char buf[MAXLINE];
  int n;

  cfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(SERV_PORT);
  inet_pton(AF_INET, "127.0.0.1", &serv_addr.sin_addr.s_addr);

  Connect(cfd, (struct sockaddr*)&serv_addr, sizeof(serv_addr));

  while(fgets(buf, MAXLINE, stdin) != NULL){
    Write(cfd, buf, strlen(buf));
    n = Read(cfd, buf, sizeof(buf));
    if(n == 0)
      printf("the other side has been closed.\n");
    else
      Write(STDOUT_FILENO, buf, n);
  }
  Close(cfd);

  return 0;
}
