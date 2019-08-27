/*************************************************************************
	> File Name: transfersManager.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月13日 星期二 16时56分06秒
 ************************************************************************/

#ifndef _TRANSFERSMANAGER_H_
#define _TRANSFERSMANAGER_H_

#include "ipc.h"
#include "transfer.h"
#include "eventsManager.h"
#include "event.h"

#define MODECOUNT 3

//#define BUFSIZE 64
struct transfersManager {
	enum mode mode;
	struct transfer* select;
	struct transfer transfers[MODECOUNT];
	struct eventsManager* eM;
	/*ipc*/
//	char txBuf[BUFSIZE];
//	char rxBuf[BUFSIZE];
	struct msgbuf tx;
	struct msgbuf rx;
	struct ipc_msg ipc;
};

#define TRANSFERSMANAGER_INIT(name) {\
		struct transfersManager* p = &name; \
		p->ipc.rcvbuf = & p->rx; \
		p->ipc.sndbuf = & p->tx; \
	p->ipc.rcvTextLen = 0; \
	p->ipc.recv_flag = 0;\
}

void tM_init(struct transfersManager* tM);
void* tM_pthread_hand_event(void*);
int tM_hand_event(struct transfersManager* tM);
void tM_hand_msg(struct transfersManager* tM);

#endif




