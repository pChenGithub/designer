
#include <stdio.h>
#include <pthread.h>
#include "pthread_task_com.h"
#include "sensorsManager.h"
#include "transfersManager.h"
#include "humansManager.h"

void pT_task_product_offline(struct pthread_task_com* pt) {
	struct runTime_object* obj = & pt->rt->object;
	struct sensorsManager* sm = obj->sm;

	sm->product_offline(sm);
}

void pT_task_product(struct pthread_task_com* pt) {
	struct runTime_object* obj = & pt->rt->object;
	struct sensorsManager* sm = obj->sm;

	sm->product(sm);
}

void pT_task_waitEvent_offline(struct pthread_task_com* pt) {
	printf("wait_event offline \n");
	sleep(3);
}
void pT_task_waitEvent(struct pthread_task_com* pt) {
	struct runTime_object* obj = & pt->rt->object;
	struct humansManager* hm = obj->hm;
	hm->wait_event(hm);
}

void* pT_thread_body(void* arg) {
	struct pthread_task_com* pt = (struct pthread_task_com*)arg;
	while(1) {
		pt->pT_task(pt);
	}
}

void pT_state_switch(struct pthread_task_com* pt, char sta) {
	switch(sta) {
	case 0:
		pt->pT_task = pt->pT_task_online;
		break;
	case 1:
		pt->pT_task = pt->pT_task_offline;
		break;
	default:
		break;
	}
}

void pT_init(struct pthread_task_com* pt, enum ptask_type type) {
	pt->type = type;
	switch(type) {
	case PRODUCT:
		pt->pT_task = pT_task_product;
		pt->pT_task_online = pT_task_product;
		pt->pT_task_offline = pT_task_product_offline;
		break;
	case WAIT_EVENT:
		pt->pT_task = pT_task_waitEvent;
		pt->pT_task_online = pT_task_waitEvent;
		pt->pT_task_offline = pT_task_waitEvent_offline;
		break;
	default:
		break;
	}
}

void pT_start(struct pthread_task_com* pt) {
	pthread_t* ppid = &pt->pid;
#if 1
	pthread_create(ppid, NULL, pt->pthread_body, pt);
	pthread_detach(*ppid);
#endif
}


