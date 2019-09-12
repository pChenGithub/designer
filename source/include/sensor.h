/*************************************************************************
	> File Name: sensor.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月12日 星期一 12时54分45秒
 ************************************************************************/

#ifndef _SENSOR_H_
#define _SENSOR_H_
#include <string.h>
#include <stdlib.h>
//#include "vol.h"
//#include "rfid.h"
#include "listNode.h"
#include "event.h"
#include "transfer.h"

struct sensor {
	struct node node;
	char name[16];
	struct sensorsManager* sM;
	void (*readData_task)(struct sensor* sensor);
	void (*sensor_init)(char* pri, struct sensor* sensor);
	void (*parse_task)(struct event* e, struct transfer* tr);
	void (*parse_task4mqtt)(struct sensor*, char*);
	char *pri;
};

#define SENSOR_INIT(s_name) ({ \
	struct sensor* sensor = malloc(sizeof(struct sensor)); \
	printf("sensor name %s \n", #s_name); \
	memcpy(sensor->name, #s_name, strlen(#s_name)+1); \
	sensor->readData_task = s_name##_readData; \
	sensor->sensor_init = s_name##_sensor_init; \
	sensor->parse_task = s_name##_parse; \
	sensor->parse_task4mqtt = s_name##_parse4mqtt; \
	sensor = sensor+0; \
}) \

#endif

