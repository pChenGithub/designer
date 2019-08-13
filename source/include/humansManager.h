/*************************************************************************
	> File Name: humansManager.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月13日 星期二 16时18分30秒
 ************************************************************************/

#ifndef _HUMANSMANAGER_H_
#define _HUMANSMANAGER_H_

#include "ipc.h"

#define BUFSIZE 64
struct humansManager {
	char h_count;
	struct node* h_list;
	/*ipc*/
	char txBuf[BUFSIZE];
	char rxBuf[BUFSIZE];
	struct ipc_msg *ipc;
};

#define HUMANSMANAGER_INIT(name) {\
	struct humansManager* p = &name; \
	p->h_count = 0; \
	p->h_list = NULL; \
	p->ipc->rcvbuf = (struct msgbuf*)(p->rxBuf); \
	p->ipc->sndbuf = (struct msgbuf*)(p->txBuf); \
}

void hM_slect_humans(void);
void hM_add_human(void);
void hM_del_hunam(void);

#endif




