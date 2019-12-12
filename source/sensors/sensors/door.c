
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sensors/door.h"
#include "../MSGService/MSGService.h"
#include "sensorsManager.h"
#include "ralink_gpio.h"

#define GPIODEV "/dev/gpio"

void door_sensor_init(char* ppri, struct sensor* sensor) {
	int fd;
	struct door_pri* pri;
	sensor->pri = malloc(sizeof(struct door_pri));
	pri = (struct door_pri*)sensor->pri;
	long tmp;

	fd = open(GPIODEV, O_RDWR);
	if (fd<0) {
		fprintf(stderr, "open  %s error \n", GPIODEV);
		return ;
	}
	pri->fd = fd;
	pri->flag = 1;
	ioctl(fd, RALINK_GPIO_READ, &tmp);
	tmp &= ~(0x1<<19);
	ioctl(fd, RALINK_GPIO_WRITE, tmp);
	ioctl(fd, RALINK_GPIO_SET_DIR_IN, 0x1<<19);
}

void door_readData(struct sensor* sensor) {
	struct door_pri* pri = (struct door_pri*)sensor->pri;
	int fd = pri->fd;
	long tmp;
	ioctl(fd, RALINK_GPIO_READ, &tmp);
	tmp = tmp&(0x1<<19);
	pri->flag = tmp?1:0;
	printf("sensor %s read value %d \n", sensor->name, tmp);
}

void door_parse(struct event* e, struct transfer* tr) {

}


void door_parse4mqtt(struct sensor* sensor, char* msg) {
	struct door_pri* pri = (struct door_pri*)sensor->pri;
	struct runTime* rt = sensor->sM->rt;
	char tmp[16]="12.63";
	char len;
	time_t t;
	t = time(NULL);
	sprintf(tmp, "%.02d", pri->flag);
#if 1
	len = strlen(tmp);
	//sprintf(msg, "pt100 get t %.02f ", dat->t);
	//086021060135000714+c+door+0+4+0.00+1571635693
	//086021060252000098+a+temperature+0+5+82.28+1571900290
	sprintf(msg, "%s+c+door+0+%d+%s+%d", rt->sn, len, tmp, t);
#endif
}



