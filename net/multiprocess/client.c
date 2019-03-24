#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <netinet/in.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <string.h>

#include "wrap.h"

#define SERV_IP "127.0.0.1"
#define SERV_PORT 8888

int main(void)
{
  int sfd, n;
  struct sockaddr_in serv_addr;
  char buf[BUFSIZ];

  sfd = Socket(AF_INET, SOCK_STREAM, 0);

  bzero(&serv_addr, sizeof(serv_addr));
  serv_addr.sin_family = AF_INET;
  serv_addr.sin_port = htons(SERV_PORT);
  inet_pton(AF_INET, SERV_IP, &serv_addr.sin_addr.s_addr);
  
  Connect(sfd, (struct sockaddr *)&serv_addr, sizeof(serv_addr));

  while(1)
  {
    fgets(buf, sizeof(buf), stdin);
    int r = Write(sfd, buf, strlen(buf));
    printf("write r...%d\n", r);
    n = Read(sfd, buf, sizeof(buf));
    printf("read n...%d\n", n);
    Write(STDOUT_FILENO, buf, n);
  }

  Close(sfd);

  return 0;
}
