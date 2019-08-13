/*************************************************************************
	> File Name: event.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月12日 星期一 16时00分11秒
 ************************************************************************/

#ifndef _EVENT_H_
#define _EVENT_H_

enum event_t {
	DATA_GET,
	NOTICE,
};

struct event {

	enum event_t type;
	char pri[32];
};

#endif
