/*************************************************************************
	> File Name: Myopen.c
	> Author: Allen
	> Mail: allen930422@gmail.com 
	> Created Time: 2020年06月15日 星期一 18时46分51秒
 ************************************************************************/

#include<stdio.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>
#include<stdlib.h>
int main()
{
	int fd;
	//打开已经存在的文件
/*	fd = open("BasicOptions.txt", O_RDWR);
	if(fd == -1){
		perror("open file");
		exit(1);
	}
*/
	//创建新文件
/*	fd = open("Myhello", O_RDWR | O_CREAT, 0777);
	if(fd == -1){
		perror("open file");
		exit(1);
	}
	printf("fd = %d\n", fd);
*/
	//判断文件是否存在
/*	fd = open("Myhello", O_RDWR | O_CREAT | O_EXCL, 0777);
	if(fd == -1){
		perror("open file");
		exit(1);
	}
*/
	//将文件截断为0
	fd = open("Myhello", O_RDWR | O_TRUNC);
	if(fd == -1){
		perror("open file");
		exit(1);
	}
	//关闭文件
	int ret = close(fd);
	printf("ret = %d\n", ret);
	if(ret == -1){
		perror("close file");
		exit(1);
	}

	return 0;
}
