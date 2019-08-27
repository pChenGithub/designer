/*************************************************************************
	> File Name: filetest.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月16日 星期五 15时15分27秒
 ************************************************************************/

#include <stdio.h>
#include "fileTools.h"

int main(int argc, char* argv[] ) {

	char* str = "hello, everyone\n";

	if (str_write_to_file("./text.txt", str)<0) {
	
		perror("write str error \n");
		return -1;
	}

	return 0;
}
