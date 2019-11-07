
#ifndef _SHT20_H_
#define _SHT20_H_
#include "sensor.h"

struct sht20_t_pri {
	int fd;
	float t;
};

struct sht20_h_pri {
	int fd;
	float h;
};

void sht20_t_sensor_init(char* pri, struct sensor* sensor);
void sht20_t_readData(struct sensor* sensor);
void sht20_t_parse(struct event* e, struct transfer* tr);
void sht20_t_parse4mqtt(struct sensor*, char*);

void sht20_h_sensor_init(char* pri, struct sensor* sensor);
void sht20_h_readData(struct sensor* sensor);
void sht20_h_parse(struct event* e, struct transfer* tr);
void sht20_h_parse4mqtt(struct sensor*, char*);
#endif
