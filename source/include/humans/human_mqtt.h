
#ifndef _HUMAN_MQTT_H_
#define _HUAMN_MQTT_H_
#include "human.h"

struct mqtt_msg_rcv {
	int uuid;
	char len;
	char event[16];
	char pri_dat[128];
};

struct human_mqtt_pri {
	struct transfer* tr;
	struct mqtt_msg_rcv msg_format;
	char buf[128];
};

void mqtt_human_init(struct human* human);
void mqtt_hand_event(struct human* human);
void mqtt_check_event(struct human* human);

#endif


