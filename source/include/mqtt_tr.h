/*************************************************************************
	> File Name: mqtt_tr.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月20日 星期二 10时25分26秒
 ************************************************************************/

#ifndef _MQTT_TR_H_
#define _MQTT_TR_H_
#include "transfer.h"
#include <mqtt.h>
#include "event.h"
//#include "templates/posix_sockets.h"

struct mqtt_tr_pri {
	struct mqtt_client client;
	char addr[16];
	char port[16];
	char topic[64];
	char application_message[256];
	uint8_t sendbuf[2048];
	uint8_t recvbuf[1024];
};

void mqtt_tr_send(struct transfer* tr);
void mqtt_tr_init(struct transfer* tr);
void mqtt_tr_reconnect(struct transfer* tr);
#endif


