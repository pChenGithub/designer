
#ifndef _HUMAN_MQTT_H_
#define _HUAMN_MQTT_H_
#include "human.h"

struct human_mqtt_pri {
	struct transfer* tr;
};

void mqtt_human_init(struct human* human);
void mqtt_hand_event(struct human* human);
void mqtt_check_event(struct human* human);

#endif


