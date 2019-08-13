/*************************************************************************
	> File Name: rfid.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月12日 星期一 16时21分25秒
 ************************************************************************/

#include <stdio.h>
#include "rfid.h"
#include "ipc.h"

void rfid_readData(char* pri) {

	struct rfid_pri* p = (struct rfid_pri*)pri;
	struct ipc_msg* ipc = (struct ipc_msg*)(p->ipc);
	struct msgbuf* msg = ipc->sndbuf;
//	enum dat_t type;

	msg->mtype = 101;
	ipc->send_flag = 0;
	ipc->sndTextLen = 10;

	memcpy(msg->data, "rfid:1234\0\0", 11);
	printf("is a rfid \n");

}

void rfid_sensor_init(char* pri, struct sensor* sensor) {

	struct rfid_pri* p = (struct rfid_pri*)pri;
	p->ipc = sensor->sM->ipc;
}





