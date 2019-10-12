/*************************************************************************
	> File Name: include/runTime.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月23日 星期五 17时48分49秒
 ************************************************************************/

#ifndef _RUNTIME_H_
#define _RUNTIME_H_
#include "object.h"

enum net_state {
	ONLINE,
	OFFLINE,
};


struct runTime {
	enum net_state n_state;
	void (*check_state)(struct runTime* rT);
	void (*check_env)(struct runTime* rt);
	struct runTime_object object;
};

void* rT_pthread_check_state(void*);
void rT_check_state(struct runTime* rT);
void rT_check_runTime_env(struct runTime* rt);
void rT_offline_runtime();
void rT_online_runtime();

#define RUNTIME_INIT(env) {\
	struct runTime* p = &env; \
	p->n_state = ONLINE; \
	p->check_state = rT_check_state; \
	p->check_env = rT_check_runTime_env; \
}\

#endif

