
#include "humans/human_mqtt.h"
#include "humansManager.h"
#include "runTime.h"

void mqtt_human_init(struct human* human) {
	struct human_mqtt_pri* pri;
	struct runTime_object* obj = & human->hM->rt->object;
	printf("mqtt human init \n");
	human->pri = malloc(sizeof(struct human_mqtt_pri));
	pri = (struct human_mqtt_pri*)human->pri;
	pri->tr = obj->tm->select;
	printf("mqtt human init done \n");
}

void mqtt_hand_event(struct human* human) {
	printf("mqtt hand event \n");
}

void mqtt_check_event(struct human* human) {
	struct human_mqtt_pri* pri;
	struct transfer* tr;
	//printf("check mqtt recv event \n");
	pri = (struct human_mqtt_pri*)human->pri;
	tr = pri->tr;
	tr->recv_data(tr);
}

