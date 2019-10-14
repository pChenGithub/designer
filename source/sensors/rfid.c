/*************************************************************************
	> File Name: rfid.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月12日 星期一 16时21分25秒
 ************************************************************************/

#include <stdio.h>
#include "rfid.h"
#include "ipc.h"
#include "mqtt_tr.h"

#ifndef TR_MQTT
#define TR_MQTT
#endif

void rfid_parse(struct event* e, struct transfer* tr) {
	struct rfid_data* dat = (struct rfid_data*)e->pri;
#ifdef TR_MQTT
	struct mqtt_tr_pri* mqtt = (struct mqtt_tr_pri*)tr->pri;
	char *msg = mqtt->application_message;
	sprintf(msg, "temperature, val: %.02f", dat->t);
#endif
}

void rfid_readData(struct sensor* sensor) {

	struct rfid_pri* p = (struct rfid_pri*)sensor->pri;
	struct event* e = (struct event*)malloc(sizeof(struct event));
	struct rfid_data* dat = (struct rfid_data*)e->pri;
	
	e->sensor = sensor;
	e->type = DATA_GET;

	dat->t = 29.5;

}

void rfid_sensor_init(char* pri, struct sensor* sensor) {

	struct rfid_pri* p = (struct rfid_pri*)pri;
	p->name = sensor->name;
}





