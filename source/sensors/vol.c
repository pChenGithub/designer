/*************************************************************************
	> File Name: vol.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月12日 星期一 16时20分31秒
 ************************************************************************/
#include <stdio.h>
#include "vol.h"
#include "ipc.h"

void vol_readData(char* pri) {
	
	struct vol_pri* p = (struct vol_pri*)pri;
	struct eventsManager* eM = p->eM;
	/*
	struct ipc_msg* ipc = (struct ipc_msg*)(p->ipc);
	struct msgbuf* msg = ipc->sndbuf;
	enum dat_t type;

	msg->mtype = 100;
	ipc->send_flag = 0;
	ipc->sndTextLen = 10;

	memcpy(msg->data, "vol:12345\0\0", 11);
*/
	struct event* e = (struct event*)malloc(sizeof(struct event));
	struct vol_data* dat;

	e->type = DATA_GET;
	dat = (struct vol_data*)(e->pri);

	dat->type = V;
	dat->val = 12.9;

	eM_add_event(eM, e);

	printf("is a vol \n");

}

void vol_sensor_init(char* pri, struct sensor* sensor) {
	struct vol_pri* p = (struct vol_pri*)pri;
	printf("vol sensor init \n");
	p->ipc = sensor->sM->ipc;
	p->eM = sensor->sM->eM;
}


