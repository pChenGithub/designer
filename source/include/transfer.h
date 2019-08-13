/*************************************************************************
	> File Name: transfer.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月13日 星期二 17时04分41秒
 ************************************************************************/

#ifndef _TRANSFER_H_
#define _TRANSFER_H_

enum mode {
	MQTT,
	SOCKET,
	BLE_OE,
};

struct transfer {
	enum mode mode;
	char name[16];
	void (*send_data)(void);
	char pri[32];
};

#endif





