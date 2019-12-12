
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sensors/press303.h"
#include "driver/read_adc.h"
#include "sensorsManager.h"

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
	pri->data.v = 0;
	pri->data.p = 0;
}

void press303_readData(struct sensor* sensor) {
	struct press303_pri* pri = (struct press303_pri*)sensor->pri;
	int fd = pri->fd;
	float tmp;
	float pressure;
	float* v = & (pri->data.v);
	float* p = & (pri->data.p);

	*v = read_adc(fd);
	tmp = *v;
	if ( tmp> 0.5) {
		//pressure = Voltage * 125 - 62.5;//0-500Kpa压力计算公式 305
		pressure = tmp * 100 - 150;//-100～300Kpa压力计算公式 303
		printf("###	pressure=%.2lf	###\n", pressure);
	}
	if (pressure <= 500.00) {
		*p = pressure;
	}else {
		printf("******	error pressure data	******\n");
		*p = 500;
	}
}

void press303_parse(struct event* e, struct transfer* tr) {

}


void press303_parse4mqtt(struct sensor* sensor, char* msg) {
	struct press303_pri* pri = (struct press303_pri*)sensor->pri;
	struct press303_data* dat = & pri->data;
	struct runTime* rt = sensor->sM->rt;
	char tmp[8];
	char len;
	time_t t;
	t = time(NULL);
	sprintf(tmp, "%.02f", dat->p);
	len = strlen(tmp);
	sprintf(msg, "%s+e+pressure+0+%d+%s+%d", rt->sn, len, tmp, t);
}

