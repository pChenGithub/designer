/*************************************************************************
	> File Name: transfersManager.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月13日 星期二 16时51分35秒
 ************************************************************************/

#include "transfersManager.h"

void* tM_pthread_hand_event(void* arg) {
	struct transfersManager* tM = (struct transfersManager*)arg;
	while(1) {
		tM_hand_event(tM);
		sleep(5);
	}
}

int tM_hand_event(struct transfersManager* tM) {
	struct eventsManager* eM = tM->eM;
	struct event* e = (struct event*)(eM->e_list);
	if (!e) {
	
		perror("event list is empty \n");
		return -1;
	}
	/* wait event */
	//e = eM->e_list;
	printf("a event \n");

	eM_del_event(eM, e);

	/* vol */


	/* mqtt */

	free(e);
}

void tM_hand_msg(struct transfersManager* tM) {
	struct ipc_msg* ipc = tM->ipc;
	struct transfer* transfer = tM->select;
	struct event* e = (struct event*)(ipc->rcvbuf->data);

	ipcMsg_recv(ipc);



	usleep(30000);
}
