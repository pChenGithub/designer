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
#include "sensors/sht20.h"
#include "runTime.h"

//#define BUFSIZE 64
struct sensorsManager {
	int freq;   // us
	struct runTime* rt;
	char s_count;
	struct node* s_list;
	int (*product)(struct sensorsManager*);
	int (*product_offline)(struct sensorsManager*);
	void (*parse)(void**, char*);
	int (*add_sensor)(struct sensorsManager* sm, struct sensor* sensor);
};

//	IPCSMG_INIT_SIMPLE(mb); 
void* sM_pthread_read(void*);
int sM_foreach_sensors(struct sensorsManager* sM);
int sM_foreach_sensors_offline(struct sensorsManager* sM);
int sM_add_sensor(struct sensorsManager* sM, struct sensor* sensor);
void sM_del_sensor(struct sensor* sensor);
void sM_init(struct sensorsManager* sM);
void sM_parse4mqtt(void** arg, char* msg);

#define SENSORSMANAGER_INIT(name, runTime) {\
	struct sensorsManager* p = &name; \
	p->freq = 3000000; \
	p->rt = &runTime; \
	p->s_count = 0; \
	p->s_list = NULL; \
	p->product = sM_foreach_sensors; \
	p->product_offline = sM_foreach_sensors_offline; \
	p->parse = sM_parse4mqtt; \
	p->add_sensor = sM_add_sensor; \
} \


#endif

