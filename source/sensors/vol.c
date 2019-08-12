/*************************************************************************
	> File Name: vol.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月12日 星期一 16时20分31秒
 ************************************************************************/

#include "vol.h"

void vol_readData(void) {

	printf("is a vol \n");
}

void vol_sensor_init(char* pri) {
	struct vol_pri* p = (struct vol_pri*)pri;
	printf("vol sensor init \n");

}
