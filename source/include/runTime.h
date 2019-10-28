/*************************************************************************
	> File Name: include/runTime.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月23日 星期五 17时48分49秒
 ************************************************************************/

#ifndef _RUNTIME_H_
#define _RUNTIME_H_
#include "object.h"
#include "common.h"

enum net_state {
	ONLINE,
	OFFLINE,
};

struct runTime {
	char sn[19];
	enum net_state n_state;
	struct current_time t; /* switch state time */
	void (*update_state_switch_time)(struct runTime* rt);
	void (*check_state)(struct runTime* rT);
	void (*check_env)(struct runTime* rt);
	struct runTime_object object;
};

void rT_update_switch_time(struct runTime* rt);
void* rT_pthread_check_state(void*);
void rT_check_state(struct runTime* rT);
void rT_check_runTime_env(struct runTime* rt);
void rT_offline_runtime();
void rT_online_runtime();

#define RUNTIME_INIT(env) {\
	struct runTime* p = &env; \
	p->n_state = ONLINE; \
	p->update_state_switch_time = rT_update_switch_time; \
	p->check_state = rT_check_state; \
	p->check_env = rT_check_runTime_env; \
}\

#endif

