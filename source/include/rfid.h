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

	char* name;
	int fd;
};

struct rfid_data {
	float t;
};

void rfid_parse(struct event* e, struct transfer* tr);
void rfid_sensor_init(char* pri, struct sensor* sensor);
void rfid_readData(struct sensor* sensor);

#endif








