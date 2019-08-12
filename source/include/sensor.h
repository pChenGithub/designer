/*************************************************************************
	> File Name: sensor.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月12日 星期一 12时54分45秒
 ************************************************************************/

#ifndef _SENSOR_H_
#define _SENSOR_H_
#include <string.h>
#include "vol.h"
#include "rfid.h"
#include "listNode.h"

struct sensor {
	struct node node;
	char name[16];
	void (*readData_task)(void);
	char pri[32];
};

#define SENSOR_INIT(s_name) ({ \
	struct sensor* sensor = malloc(sizeof(struct sensor)); \
	printf("sensor name %s \n", #s_name); \
	memcpy(sensor->name, #s_name, strlen(#s_name)+1); \
	sensor->readData_task = s_name##_readData; \
	s_name##_sensor_init(sensor->pri); \
	sensor = sensor+0; \
}) \

#endif

