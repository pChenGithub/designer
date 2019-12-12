/*************************************************************************
	> File Name: transfersManager.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月13日 星期二 16时51分35秒
 ************************************************************************/

#include "transfersManager.h"
#include "mqtt_tr.h"

void tM_init(struct transfersManager* tM) {
	struct transfer* transfer;

	transfer = tM->transfers;
	TRANSFER_INIT(transfer, MQTT, mqtt);
	transfer->tm = tM;

	tM->mode = MQTT;
	tM->select = tM->transfers;
	tM->select->transfer_init(tM->select);
}

void* tM_pthread_hand_event(void* arg) {
	struct transfersManager* tM = (struct transfersManager*)arg;

	while(1) {
//		sleep(5);
	}
}

int tM_hand_event(struct transfersManager* tM) {
}

void tM_hand_msg(struct transfersManager* tM) {
	struct transfer* transfer = tM->select;
	usleep(30000);
}


