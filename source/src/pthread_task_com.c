
#include <stdio.h>
#include <pthread.h>
#include "pthread_task_com.h"

void* pT_task_product(void* arg) {
	struct pthread_task_com* pt = (struct pthread_task_com*)arg;
	struct sensorsManager* sM = pt->sM;
	struct transfersManager* tM = pt->tM;
	while(1) {
		pt->product(sM);
		pt->consume(tM);
	}
}

void* pT_task_waitEvent(void* arg) {
	struct pthread_task_com* pt = (struct pthread_task_com*)arg;
	pt->wait_event();
}

void pT_init(struct pthread_task_com* pt, enum ptask_type type) {
	pthread_t* ppid = &pt->pid;
	struct sensorsManager* sM = pt->sM;
	struct humansManager* hM = pt->hM;
	struct transfersManager* tM = pt->tM;
	pt->type = type;
	switch(type) {
	case PRODUCT:
		pt->pT_task = pT_task_product;
		pt->product = sM->product;
		pt->consume = tM->consume;
		break;
	case WAIT_EVENT:
		pt->pT_task = pT_task_waitEvent;
		pt->wait_event = hM->wait_event;
		break;
	default:
		break;
	}
#if 1
	pthread_create(ppid, NULL, pt->pT_task, pt);
	pthread_detach(*ppid);
#endif
}


