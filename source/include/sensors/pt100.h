
#ifndef _PT100_H_
#define _PT100_H_
#include "sensor.h"

struct pt100_data {
	float v;
	float r;
	float t;
};

struct pt100_pri {
	int fd;
	float zero;
	struct pt100_data data;
};

void pt100_sensor_init(char* pri, struct sensor* sensor);
void pt100_readData(struct sensor* sensor);
void pt100_parse(struct event* e, struct transfer* tr);
void pt100_parse4mqtt(struct sensor*, char*);
#endif
