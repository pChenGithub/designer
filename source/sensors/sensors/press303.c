
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sensors/press303.h"
#include "driver/read_adc.h"
#define ADC6 "/dev/ads1015_6"


void press303_sensor_init(char* ppri, struct sensor* sensor) {
	int fd;
	struct press303_pri* pri;
	sensor->pri = malloc(sizeof(struct press303_pri));
	pri = (struct press303_pri*)sensor->pri;

	fd = open(ADC6, O_RDONLY);
	if (fd<0) {
		fprintf(stderr, "open  %s error \n", ADC6);
		return ;
	}

	pri->fd = fd;
}

void press303_readData(struct sensor* sensor) {
	struct press303_pri* pri = (struct press303_pri*)sensor->pri;
	int fd = pri->fd;
	float* v = & (pri->data.v);
	float* p = & (pri->data.p);

	*v = read_adc(fd);

	printf("sensor %s read value %f \n", sensor->name, *v);

}

void press303_parse(struct event* e, struct transfer* tr) {

}


void press303_parse4mqtt(struct sensor* sensor, char* msg) {
	struct press303_pri* pri = (struct press303_pri*)sensor->pri;
	struct press303_data* dat = & pri->data;

	sprintf(msg, "press303 get v %.02f ", dat->v);
}

