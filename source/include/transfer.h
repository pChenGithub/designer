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
	void (*recv_data)(struct transfer* tr, char* msg);
	void (*transfer_init)(struct transfer* tr);
	void (*transfer_reconnect)(struct transfer* tr);
	char* pri;
};

#define TRANSFER_INIT(transfer, MQTT, name_s) { \
	transfer->mode = MQTT; \
	memcpy(transfer->name, #name_s, strlen(#name_s)+1); \
	transfer->send_data = name_s##_tr_send; \
	transfer->recv_data = name_s##_tr_recv; \
	transfer->transfer_init = name_s##_tr_init; \
	transfer->transfer_reconnect = name_s##_tr_reconnect; \
}\

#endif





