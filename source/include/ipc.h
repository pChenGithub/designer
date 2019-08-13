/*************************************************************************
	> File Name: ipc_msg.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年03月22日 星期五 14时56分21秒
 ************************************************************************/

#ifndef _IPC_H_
#define _IPC_H_

#include<stdio.h>
#include <sys/types.h>
#include <sys/ipc.h>
#include <errno.h>
#include <sys/msg.h>
#include <string.h>
#include <unistd.h>


struct msgbuf {
	long mtype;
	char data[0];
};

struct ipc_msg {
	int msgId;
	struct msgbuf* rcvbuf;
	size_t rcvTextLen;
	int recv_flag;
	struct msgbuf* sndbuf;
	size_t sndTextLen;
	int send_flag;
};

enum chanel_t {
	CHANEL_1 = 10,
	CHANEL_2,
	CHANEL_3,
	CHANEL_4,
	CHANEL_5,
};

int ipcMsg_init(struct ipc_msg *msgQuque, const char *file, const char c);
int ipcMsg_recv(struct ipc_msg *msgQuque);
int ipcMsg_send(struct ipc_msg *msgQuque);

#define IPCSMG_INIT(name) { \
	struct ipc_msg* p = &name; \
	ipcMsg_init(p, "/", 'x'); \
}

#endif

