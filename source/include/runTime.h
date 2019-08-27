/*************************************************************************
	> File Name: include/runTime.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月23日 星期五 17时48分49秒
 ************************************************************************/

#ifndef _RUNTIME_H_
#define _RUNTIME_H_

enum net_state {
	ONLINE,
	OFFLINE,
};

struct runTime {
	enum net_state n_state;
	void (*check_state)(void);
};

void* rT_pthread_check_state(void*);
void rt_check_state(void);

#endif

