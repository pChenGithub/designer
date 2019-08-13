/*************************************************************************
	> File Name: transfersManager.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月13日 星期二 16时51分35秒
 ************************************************************************/

#include "transfersManager.h"

void tM_hand_msg(struct transfersManager* tM) {
	struct ipc_msg* ipc = tm->ipc;
	struct transfer* transfer = tM->select;
	struct event* e = (struct event)(ipc->rcvbuf->data);

	ipcMsg_recv(ipc);



	usleep(30000);
}
