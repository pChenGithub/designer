/*************************************************************************
	> File Name: fileTools.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月16日 星期五 14时01分25秒
 ************************************************************************/

#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include "fileTools.h"

int str_write_to_file(const char* file, const char* str) {

	int fd;
	int nw;

	if ((fd = open(file, O_WRONLY|O_CREAT|O_EXCL|O_APPEND, 0666))<0) {
		if (errno==EEXIST) {
			if ((fd = open(file, O_WRONLY|O_APPEND))<0) {
				perror("open file error \n");
				return -1;
			}
		}
	}

	printf("fd %d, \n", fd);

	nw = write(fd, str, strlen(str));
	if (nw!=strlen(str)) {
		perror("write file error, again \n");
	}

	close(fd);

	return nw;
}

