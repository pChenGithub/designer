/*************************************************************************
	> File Name: rfid.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月12日 星期一 16时08分51秒
 ************************************************************************/

#ifndef _RFID_H_
#define _RFID_H_

#include "sensor.h"
#include "sensorsManager.h"

struct rfid_pri {

	int fd;
	struct ipc_msg* ipc;
};

void rfid_sensor_init(char* pri, struct sensor* sensor);
void rfid_readData(char* pri);

#endif








