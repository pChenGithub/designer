/*************************************************************************
	> File Name: sensorsManager.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月12日 星期一 12时38分57秒
 ************************************************************************/

#ifndef _SENSORSMANAGER_H_
#define _SENSORSMANAGER_H_

#include <ipc.h>
#include <sensor.h>
#include "eventsManager.h"
#include "sensors/pt100.h"
#include "sensors/press303.h"

//#define BUFSIZE 64
struct sensorsManager {
	int freq;   // us
	char s_count;
	void (*product)(struct sensorsManager*);
	void (*parse)(void**, char*);
	struct node* s_list;
	struct eventsManager* eM;
	/*ipc*/
	struct msg_body mq;
	struct ipc_msg* ipc;
};

//	IPCSMG_INIT_SIMPLE(mb); 
void* sM_pthread_read(void*);
int sM_foreach_sensors(struct sensorsManager* sM);
int sM_add_sensor(struct sensorsManager* sM, struct sensor* sensor);
void sM_del_sensor(struct sensor* sensor);
void sM_init(struct sensorsManager* sM);
void sM_parse4mqtt(void** arg, char* msg);

#define SENSORSMANAGER_INIT(name) {\
	struct sensorsManager* p = &name; \
	struct msg_body* mb = &p->mq; \
	p->freq = 3000000; \
	p->s_count = 0; \
	p->s_list = NULL; \
	p->product = sM_foreach_sensors; \
	p->parse = sM_parse4mqtt; \
	p->ipc = &(p->mq.ipc); \
	IPCSMG_INIT_SIMPLE(mb); \
}

#endif

