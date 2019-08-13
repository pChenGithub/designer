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

#define MODECOUNT 3

#define BUFSIZE 64
struct transfersManager {
	enum mode mode;
	struct transfer* select;
	struct transfer transfers[MODECOUNT];
	/*ipc*/
	char txBuf[BUFSIZE];
	char rxBuf[BUFSIZE];
	struct ipc_msg* ipc;
};

#define TRANSFERSMANAGER_INIT(name) {\
		struct transfersManager* p = &name; \
		p->ipc->rcvbuf = (struct msgbuf*)(p->rxBuf); \
		p->ipc->sndbuf = (struct msgbuf*)(p->txBuf); \
}

void tM_hand_msg(void);

#endif




