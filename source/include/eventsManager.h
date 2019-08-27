/*************************************************************************
	> File Name: eventsManager.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月14日 星期三 13时36分32秒
 ************************************************************************/

#ifndef _EVENTSMANAGER_H_
#define _EVENTSMANAGER_H_

#include "event.h"
#include "listNode.h"
#include "sensorsManager.h"

struct eventsManager {
	char e_count;
	struct node* e_list;
	struct sensorsManager* sM;
	/* ipc */
	struct msgbuf tx;
	struct msgbuf rx;
	struct ipc_msg ipc;
};

void eM_init(struct eventsManager* eM);
int eM_add_event(struct eventsManager* eM, struct event* event);
int eM_del_event(struct eventsManager* eM, struct event* event);

#define EVENTSMANAGER_INIT(name) { \
	struct eventsManager* p = &name; \
	p->ipc.rcvbuf = & p->rx; \
	p->ipc.sndbuf = & p->tx; \
	p->ipc.rcvTextLen = 0; \
	p->ipc.recv_flag = 0; \
	p->ipc.sndTextLen = 0; \
	p->ipc.send_flag = 0; \
}

#endif


