/*************************************************************************
	> File Name: vol.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月12日 星期一 15时04分47秒
 ************************************************************************/

#ifndef _VOL_H_
#define _VOL_H_

#include "event.h"

struct vol_pri {

	int fd;
};

void vol_sensor_init(char* pri);
void vol_readData(void);
#endif



