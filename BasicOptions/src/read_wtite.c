/*************************************************************************
	> File Name: src/read_wtite.c
	> Author: Allen
	> Mail: allen930422@gmail.com 
	> Created Time: 2020年06月16日 星期二 10时42分51秒
 ************************************************************************/

#include<stdio.h>
#include<stdlib.h>
#include<sys/types.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

int main()
{
	int fd;
	//打开一个已经存在的文件
	fd = open("english.txt", O_RDONLY);
	if(fd == -1){
		perror("open file");
		exit(1);
	}

	//创建一个新文件  -- 写操作
	int fd1 = open("newfile", O_CREAT | O_WRONLY, 0664);
	if(fd1 == -1){
		perror("open1 file");
		exit(1);
	}

	//read file
	char buf[2048] = {0};
	int count = read(fd, buf, sizeof(buf));
	if(count == -1){
		perror("read");
		exit(1);
	}
	while(count){
		//将读出的数据写入另一个文件中
		int ret = write(fd1, buf, count);
		printf("write bytes %d\n", ret);
		//continue read file
		count = read(fd, buf, sizeof(buf));
	}

	//close file
	close(fd);
	close(fd1);

	return 0;
}
