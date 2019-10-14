
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sensors/pt100.h"
#include "driver/read_adc.h"
#define ADC0 "/dev/ads1015_0"

#define BELOW_LOW_LIMITE 0xcccc
#define EXCESS_UP_LIMITE 0xffff

static float RTD_TAB_PT100[] = {
18.52,20.68,22.83,24.97,27.10,29.22,31.34,33.44,35.54,37.64,                  // -200 ~ -155   10
39.72,41.80,43.88,45.94,48.00,50.06,52.11,54.15,56.19,58.23,                  // -150 ~ -105
60.26,62.28,64.30,66.31,68.33,70.33,72.33,74.33,76.33,78.32,                  // -100 ~ -55
80.31,82.29,84.27,86.25,88.22,90.19,92.16,94.12,96.09,98.04,                  // -50 ~ -5
100.00,101.95,103.90,105.85,107.79,109.73,111.67,113.61,115.54,117.47,        // 0   ~ 45
119.40,121.32,123.24,125.16,127.08,128.99,130.90,132.80,134.71,136.61,        // 50  ~ 95
138.51,140.40,142.29,144.18,146.07,147.95,149.83,151.71,153.58,155.46,        // 100 ~ 145
157.33,159.19,161.05,162.91,164.77,166.63,168.48,170.33,172.17,174.02,        // 150 ~ 195
175.86,177.69,179.53,181.36,183.19,185.01,186.84,188.66,190.47,192.29,        // 200 ~ 245
194.10,195.91,197.71,199.51,201.31,203.11,204.90,206.70,208.48,210.27,        // 250 ~ 295
212.05,213.83,215.61,217.38,219.15,220.92,222.68,224.45,226.21,227.96,        // 300 ~ 345
229.72,231.47,233.21,234.96,236.70,238.44,240.18,241.91,243.64,245.37,        // 350 ~ 395
247.09,248.81,250.53,252.25,253.96,255.67,257.38,259.08,260.78,262.48,        // 400 ~ 445
264.18,265.87,267.56,269.25,270.93,272.61,274.29,275.97,277.64,279.31,        // 450 ~ 495
280.98,282.64,284.30,285.96,287.62,289.27,290.92,292.56,294.21,295.85,        // 500 ~ 545
297.49,299.12,300.75,302.38,304.01,305.63,307.25,308.87,310.49,312.10,        // 550 ~ 595
313.71,315.31,316.92,318.52,320.12,321.71,323.30,324.89,326.48,328.06,        // 600 ~ 645
329.64,331.22,332.79,334.36,335.93,337.50,339.06,340.62,342.18,343.73,        // 650 ~ 695
345.28,346.83,348.38,349.92,351.46,353.00,354.53,356.06,357.59,359.12,        // 700 ~ 745
360.64,362.16,363.67,365.19,366.70,368.21,369.71,371.21,372.71,374.21,        // 750 ~ 795
375.70,377.19,378.68,380.17,381.65,383.13,384.60,386.08,387.55,389.02,        // 800 ~ 845
390.48																		  // 850
};

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

float CalculateTemperature(float fR)
{
	float fTem;
	float fLowRValue;
	float fHighRValue;
	int   iTem;
	unsigned char i;
	unsigned char cLimite = 0xFF;
	unsigned char cBottom, cTop;
	// 电阻值小于表格最值低于量程下限。
	if (fR < RTD_TAB_PT100[0])
	{
		return BELOW_LOW_LIMITE;
	}
	// 电阻值大于表格最大值，超出量程上限 。
	if (fR > RTD_TAB_PT100[210])
	{
		return EXCESS_UP_LIMITE;
	}
	cBottom = 0;
	cTop = 210;
	for (i = 105; (cTop - cBottom) != 1; )// 2分法查表。
	{
		if (fR < RTD_TAB_PT100[i]){
			cTop = i;
			i = (cTop + cBottom) / 2;
		}
		else if (fR > RTD_TAB_PT100[i]){
			cBottom = i;
			i = (cTop + cBottom) / 2;
		}
		else{
			iTem = (uint)i * 5 - 200;
			fTem = (float)iTem;
			return fTem;
		}
	}
	iTem = (uint)i * 5 - 200;
	fLowRValue = RTD_TAB_PT100[cBottom];
	fHighRValue = RTD_TAB_PT100[cTop];
	fTem = (((fR - fLowRValue) * 5) / (fHighRValue - fLowRValue)) + iTem;	// 表格是以5度为一步的。
																			// 两点内插进行运算。
	return fTem;
}

void pt100_readData(struct sensor* sensor) {
	struct pt100_pri* pri = (struct pt100_pri*)sensor->pri;
	int fd = pri->fd;
	float tmp;
	float* v = & (pri->data.v);
	float* r = & (pri->data.r);
	float* t = & (pri->data.t);

	*v = read_adc(fd);
	tmp = *v;
	*r = tmp*1000/(3.34-tmp);
	*t = CalculateTemperature(*r);

	printf("sensor %s read value %f \n", sensor->name, *v);

}

void pt100_parse(struct event* e, struct transfer* tr) {

}


void pt100_parse4mqtt(struct sensor* sensor, char* msg) {
	struct pt100_pri* pri = (struct pt100_pri*)sensor->pri;
	struct pt100_data* dat = & pri->data;

	sprintf(msg, "pt100 get t %.02f ", dat->t);
}

