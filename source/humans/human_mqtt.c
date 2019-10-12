
#include "humans/human_mqtt.h"
#include "humansManager.h"

void mqtt_human_init(struct human* human) {
	struct human_mqtt_pri* pri;
	printf("mqtt human init \n");
	human->pri = malloc(sizeof(struct human_mqtt_pri));
	pri = (struct human_mqtt_pri*)human->pri;
	pri->tr = human->hM->tM->select;
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

