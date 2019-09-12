/*************************************************************************
	> File Name: transfer.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月13日 星期二 17时04分41秒
 ************************************************************************/

#ifndef _TRANSFER_H_
#define _TRANSFER_H_
#include "event.h"
enum mode {
	MQTT,
	SOCKET,
	BLE_OE,
};

struct transfer {
	enum mode mode;
	char name[16];
	void (*send_data)(struct transfer* tr);
	void (*transfer_init)(struct transfer* tr);
	void (*transfer_reconnect)(struct transfer* tr);
	char* pri;
};

#define TRANSFER_INIT(transfer, MQTT, name_s, mqtt_send, mqtt_init) { \
	transfer->mode = MQTT; \
	memcpy(transfer->name, #name_s, strlen(#name_s)+1); \
	transfer->send_data = mqtt_send; \
	transfer->transfer_init = mqtt_init; \
}

#endif





