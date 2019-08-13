/*************************************************************************
	> File Name: example/ipc_test.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月13日 星期二 12时54分38秒
 ************************************************************************/

#include <stdio.h>
#include "ipc.h"

char rxBuf[64];
struct ipc_msg ipc_msg;

int main(int argc, char* argv[] ) {

	struct msgbuf* msg;
	IPCSMG_INIT(ipc_msg);
	ipc_msg.rcvbuf = rxBuf;
	ipc_msg.recv_flag = 0;
	ipc_msg.rcvTextLen = 10;

	msg = ipc_msg.rcvbuf;


	while(1) {
	
		msg->mtype = 0;
		ipcMsg_recv(&ipc_msg);
		printf("msg: type %d, ** %s ** \n", msg->mtype, msg->data);

	}

	return 0;
}
