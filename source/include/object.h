
#ifndef _OBJECT_H_
#define _OBJECT_H_
#include "sensorsManager.h"
#include "humansManager.h"
#include "transfersManager"
#include "pthread_task_com.h"

struct runTime_object {
	struct sensorsManager* sm;
	struct humansManager* hm;
	struct transfersManager* tm;
	struct pthread_task_com* task_product;
	struct pthread_task_com* task_wait_event;
};

#endif

