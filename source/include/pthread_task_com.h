
#ifndef _PTHREAD_TASK_COM_H_
#define _PTHREAD_TASK_COM_H_
#include "sensorsManager.h"
#include "transfersManager.h"

enum ptask_type {
	PRODUCT,
	WAIT_EVENT,
};

struct pthread_task_com {
	enum ptask_type type;
	pthread_t pid;
	void* (*pT_task)(void*);
	void (*product)(struct sensorsManager*);
	void (*consume)(struct transfersManager*);
	void (*wait_event)(void);
	void (*handle_event)(void);
	struct sensorsManager* sM;
	struct transfersManager* tM;
};

static void* pT_task_product(void*);
static void* pT_task_waitEvent(void*);

void pT_init(struct pthread_task_com *pt, enum ptask_type type);

#endif


