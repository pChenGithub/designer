
#include <stdio.h>
#include "driver/read_adc.h"

float read_adc(int fd) {
	short tmp;
	float Voltage;
	if (read(fd, &tmp, 4)<0) {
		perror("read adc error \n");
		return -1;
	}
	printf("adc tmo %d \n", tmp);

	Voltage = tmp*6.144/32768;
	printf("adc v: %f V \n", Voltage);

	return Voltage;
}
