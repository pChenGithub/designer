/*************************************************************************
	> File Name: rfid.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月12日 星期一 16时08分51秒
 ************************************************************************/

#ifndef _RFID_H_
#define _RFID_H_

struct rfid_pri {

	int fd;
};

void rfid_sensor_init(char* pri);
void rfid_readData(void);

#endif








