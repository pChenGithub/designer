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

#define BUFSIZE 64
struct sensorsManager {
	int freq;   // us
	char s_count;
	struct node* s_list;
	struct eventsManager* eM;
	/*ipc*/
	char txBuf[BUFSIZE];
	char rxBuf[BUFSIZE];
	struct ipc_msg* ipc;
};

#define SENSORSMANAGER_INIT(name) {\
	struct sensorsManager* p = &name; \
	p->freq = 3000000; \
	p->s_count = 0; \
	p->s_list = NULL; \
	p->ipc->rcvbuf = (struct msgbuf*)(p->rxBuf); \
	p->ipc->sndbuf = (struct msgbuf*)(p->txBuf); \
}

void* sM_pthread_read(void*);
int sM_foreach_sensors(struct sensorsManager* sM);
int sM_add_sensor(struct sensorsManager* sM, struct sensor* sensor);
void sM_del_sensor(struct sensor* sensor);

#endif

