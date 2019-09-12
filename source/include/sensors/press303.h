
#ifndef _PRESS303_H_
#define _PRESS303_H_
#include "sensor.h"

struct press303_data {
	float v;
	float p;
};

struct press303_pri {
	int fd;
	struct press303_data data;
};

void press303_sensor_init(char* pri, struct sensor* sensor);
void press303_readData(struct sensor* sensor);
void press303_parse(struct event* e, struct transfer* tr);
void press303_parse4mqtt(struct sensor*, char*);
#endif
