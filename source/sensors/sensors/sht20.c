
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include "sensors/sht20.h"
#include "driver/read_adc.h"
#include "../MSGService/MSGService.h"
#include "sensorsManager.h"
#include "i2c_drv.h"

void i2c_reset(void)
{
	int fd = 0;
	int ret = 0;
	printf("-------------i2c_reset\n");
	fd = open("/dev/"I2C_DEV_NAME, O_RDONLY);
	ret = ioctl(fd, RT5350_I2C_SHT30_RESET, NULL);
	if (ret < 0) {
		perror("SHT30 reset failed");
	}
	ret = ioctl(fd, RT5350_I2C_SDP600_RESET, NULL);
	if (ret < 0) {
		perror("SDP600 reset failed");
	}
	system("gpio l 20 0 4000 0 1 4000");
	sleep(3);
	close(fd);
	system("gpio l 20 4000 0 1 0 4000");
	sleep(3);
}

static int SDP600_CheckCrc(unsigned char data[], unsigned char nbrOfBytes, unsigned char checksum)
{
	unsigned char bit;        // bit mask
	unsigned char crc = 0x00; // calculated checksum
	unsigned char byteCtr;    // byte counter
	//#define POLYNOMIAL  0x131    // CRC校验 P(x) = x^8 + x^5 + x^4 + 1 = 100110001
	// calculates 8-Bit checksum with given polynomial
	for (byteCtr = 0; byteCtr < nbrOfBytes; byteCtr++)
	{
		crc ^= (data[byteCtr]);
		for (bit = 8; bit > 0; --bit)
		{
			if (crc & 0x80) crc = (crc << 1) ^ 0x131;
			else           crc = (crc << 1);
		}
	}
	// verify checksum
	if (crc != checksum) return -1;
	else                return 0; // checksum mismatch erro
}

void sht20_t_sensor_init(char* ppri, struct sensor* sensor) {
	struct sht20_t_pri* pri;
	sensor->pri = malloc(sizeof(struct sht20_t_pri));
	pri = (struct sht20_t_pri*)sensor->pri;
}

void sht20_t_readData(struct sensor* sensor) {
	struct sht20_t_pri* pri = (struct sht20_t_pri*)sensor->pri;
	static int i;
	int ret;
	int fd;
	char data[6];
	long val_T;
	i++;
	if (i > 10000) {
		//	softreset
	}
#if TWO
	system("gpio l 20 4000 0 1 0 4000");
	sleep(3);
#endif 
	fd = open("/dev/"I2C_DEV_NAME, O_RDONLY);
	memset(data, 0, sizeof(data));
	ret = ioctl(fd, RT5350_I2C_SHTX_T_START, &data);
	if (ret < 0) {
		perror("SHT20ReadTemperature-ad0: fail");
	}
	usleep(300 * 1000);//delay 300ms
	ret = ioctl(fd, RT5350_I2C_SHTX_T_READ, &data);
	if (ret < 0) {
		perror("SHT20ReadTemperature-ad1: fail");
	}

	close(fd);
#if TWO
	system("gpio l 20 0 4000 0 1 4000");
#endif 
	if (SDP600_CheckCrc(data, 2, data[2]) != 0 || (data[0] == 0 && data[1] == 0 && data[2] == 0)) {
		return ;
	}

	val_T = ((data[0] & 0xff) << 8 | (data[1] & 0xff)) & 0xfffb;
	val_T = ((1000 * 175.72*val_T) / 65536) - (1000 * 46.85);

#if DEBUG
	printf("LIBDRI::: val_T=%d -- %x %x %x\n", val_T, data[0], data[1], data[2]);
#endif	
#if 1
	if (val_T < 0 || val_T>100000) {
		i2c_reset();
		val_T = -1;
	}
#endif
	pri->t = val_T/1000.0;
}

void sht20_t_parse(struct event* e, struct transfer* tr) {

}


void sht20_t_parse4mqtt(struct sensor* sensor, char* msg) {
	struct sht20_t_pri* pri = (struct sht20_t_pri*)sensor->pri;
	struct runTime* rt = sensor->sM->rt;
	char tmp[16];
	char len;
	time_t t;
	t = time(NULL);
	sprintf(tmp, "%.02f", pri->t);
	len = strlen(tmp);
#if 0
	len = strlen(tmp);
	//sprintf(msg, "pt100 get t %.02f ", dat->t);
	//086021060135000714+c+door+0+4+0.00+1571635693
	//086021060252000098+a+temperature+0+5+82.28+1571900290
	sprintf(msg, "%s+a+temperature+0+%d+%s+%d", rt->sn, len, tmp, t);
#endif
	//sprintf(msg, "%s-t:%.02f", "sht20_t", pri->t);
	sprintf(msg, "%s+b+temperature+0+%d+%s+%d", rt->sn, len, tmp, t);
}

void sht20_h_sensor_init(char* ppri, struct sensor* sensor) {
	sensor->pri = malloc(sizeof(struct sht20_h_pri));
}

void sht20_h_readData(struct sensor* sensor) {
	struct sht20_h_pri* pri = (struct sht20_h_pri*)sensor->pri;
	int ret;
	int fd;
	char data[6];
	long val_H;
#if TWO
	system("gpio l 20 4000 0 1 0 4000");
	sleep(3);
#endif 
	fd = open("/dev/"I2C_DEV_NAME, O_RDONLY);
	memset(data, 0, sizeof(data));

	ret = ioctl(fd, RT5350_I2C_SHTX_H_START, &data);
	if (ret < 0) {
		perror("SHT20ReadHumidity-ad0: fail");
	}
	usleep(100 * 1000);//delay 300ms
	ret = ioctl(fd, RT5350_I2C_SHTX_H_READ, &data);
	if (ret < 0) {
		perror("SHT20ReadHumidity-ad1: fail");
	}
	close(fd);
#if TWO
	system("gpio l 20  0  4000  0 1 4000");
#endif 

	if (SDP600_CheckCrc(data, 2, data[2]) != 0 || (data[0] == 0 && data[1] == 0 && data[2] == 0)) {
		return ;
	}
	val_H = ((data[0] & 0xff) << 8 | (data[1] & 0xff)) & 0xfff0;
	val_H = ((1000 * 125.0*val_H) / 65536) - (1000 * 6);//mutiple by 1000
#if DEBUG
	printf("LIBDRI:::  val_H=%d --- %x %x %x\n", val_H, data[0], data[1], data[2]);
#endif
	if (val_H < 0 || val_H> 100000) {
		i2c_reset();
		val_H = -1;
	}
	pri->h = val_H/1000.0;
}

void sht20_h_parse(struct event* e, struct transfer* tr) {

}


void sht20_h_parse4mqtt(struct sensor* sensor, char* msg) {
	struct sht20_h_pri* pri = (struct sht20_h_pri*)sensor->pri;
	struct runTime* rt = sensor->sM->rt;
	char tmp[16];
	char len;
	time_t t;
	t = time(NULL);
	sprintf(tmp, "%.02f", pri->h);
	len = strlen(tmp);
	sprintf(msg, "%s+b+humidity+0+%d+%s+%d", rt->sn, len, tmp, t);
}




