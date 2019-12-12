
#ifndef _DOOR_H_
#define _DOOR_H_
#include "sensor.h"

struct door_pri {
	int fd;
	char flag;
};

void door_sensor_init(char* pri, struct sensor* sensor);
void door_readData(struct sensor* sensor);
void door_parse(struct event* e, struct transfer* tr);
void door_parse4mqtt(struct sensor*, char*);
#endif


