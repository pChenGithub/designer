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

	tM->mode = MQTT;
	tM->select = tM->transfers;
	tM->select->transfer_init(tM->select);
}

void* tM_pthread_hand_event(void* arg) {
	struct transfersManager* tM = (struct transfersManager*)arg;
	struct eventsManager* eM = tM->eM;
	struct ipc_msg* ipc = & tM->ipc;

	while(1) {
		ipc->rcvbuf->mtype = CHANEL_1;
		ipcMsg_recv(ipc);
		printf("event count: %d \n", eM->e_count);
		tM_hand_event(tM);
//		sleep(5);
	}
}

int tM_hand_event(struct transfersManager* tM) {
	struct eventsManager* eM = tM->eM;
	struct event* e = (struct event*)(eM->e_list);
	struct transfer* transfer = tM->select;
	if (!e) {
	
		perror("event list is empty \n");
		return -1;
	}
	/* wait event */
	printf("a event \n");

	eM_del_event(eM, e);

	/* vol */


	/* mqtt */
//	transfer->send_data(transfer, e);

	free(e);
}

void tM_hand_msg(struct transfersManager* tM) {
	struct ipc_msg* ipc = & tM->ipc;
	struct transfer* transfer = tM->select;
	struct event* e = (struct event*)(ipc->rcvbuf->data);

	ipcMsg_recv(ipc);



	usleep(30000);
}

void tM_consume(struct transfersManager* tM) {
	struct transfer* tr = tM->select;
	struct mqtt_tr_pri* pri = (struct mqtt_tr_pri*)tr->pri;
	char* msg = pri->application_message;
	struct sensorsManager* sM = tM->sM;
	char count = sM->s_count;
	void* node = sM->s_list;
	while(count--) {
		sM->parse(&node, msg);
		tr->send_data(tr);
	}

}


