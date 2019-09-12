
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sensors/pt100.h"
#include "driver/read_adc.h"
#define ADC0 "/dev/ads1015_0"


void pt100_sensor_init(char* ppri, struct sensor* sensor) {
	int fd;
	struct pt100_pri* pri;
	sensor->pri = malloc(sizeof(struct pt100_pri));
	pri = (struct pt100_pri*)sensor->pri;

	fd = open(ADC0, O_RDONLY);
	if (fd<0) {
		fprintf(stderr, "open  %s error \n", ADC0);
		return ;
	}

	pri->fd = fd;
}

void pt100_readData(struct sensor* sensor) {
	struct pt100_pri* pri = (struct pt100_pri*)sensor->pri;
	int fd = pri->fd;
	float* v = & (pri->data.v);
	float* r = & (pri->data.r);
	float* t = & (pri->data.t);

	*v = read_adc(fd);

	printf("sensor %s read value %f \n", sensor->name, *v);

}

void pt100_parse(struct event* e, struct transfer* tr) {

}


void pt100_parse4mqtt(struct sensor* sensor, char* msg) {
	struct pt100_pri* pri = (struct pt100_pri*)sensor->pri;
	struct pt100_data* dat = & pri->data;

	sprintf(msg, "pt100 get v %.02f ", dat->v);
}

