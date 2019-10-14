
#ifndef _PTHREAD_TASK_COM_H_
#define _PTHREAD_TASK_COM_H_
#include "object.h"
#include "runTime.h"

enum ptask_type {
	PRODUCT,
	WAIT_EVENT,
};

struct pthread_task_com {
	enum ptask_type type;
	pthread_t pid;
	struct runTime* rt;
	void (*init)(struct pthread_task_com* pt, enum ptask_type type);
	void (*start)(struct pthread_task_com *pt);
	void (*state_switch)(struct pthread_task_com* pt, char sta);
	void* (*pthread_body)(void*);
	void (*pT_task)(struct pthread_task_com* pt);
	void (*pT_task_online)(struct pthread_task_com* pt);
	void (*pT_task_offline)(struct pthread_task_com* pt);
};

static void pT_task_product(struct pthread_task_com* pt);
static void pT_task_waitEvent(struct pthread_task_com* pt);

void pT_state_switch(struct pthread_task_com* pt, char sta);
void* pT_thread_body(void*);
void pT_init(struct pthread_task_com *pt, enum ptask_type type);
void pT_start(struct pthread_task_com *pt);

#define PTHREAD_TASK_INIT(task, runTime) { \
	struct pthread_task_com* p = &task; \
	p->init = pT_init; \
	p->start = pT_start; \
	p->state_switch = pT_state_switch; \
	p->pthread_body = pT_thread_body; \
	p->rt = &runTime; \
} \


#endif


