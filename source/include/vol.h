/*************************************************************************
	> File Name: vol.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月12日 星期一 15时04分47秒
 ************************************************************************/

#ifndef _VOL_H_
#define _VOL_H_

#include "event.h"
#include "sensor.h"
#include "sensorsManager.h"

struct vol_pri {
	char* name;
	int fd;
	struct ipc_msg* ipc;
};

enum dat_t {
	V,
	I,
	P
};

struct vol_data {
	enum dat_t type;
	float val;
};

void vol_sensor_init(char* pri, struct sensor* sensor);
void vol_readData(char* pri);
#endif



