/*************************************************************************
	> File Name: ipc_msg.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年03月22日 星期五 13时41分09秒
 ************************************************************************/

#include "ipc.h"

int ipcMsg_send(struct ipc_msg *msgQuque) {
	int msgId = msgQuque->msgId;
	struct msgbuf *msg = msgQuque->sndbuf;
	size_t sndTextLen = msgQuque->sndTextLen;
	int send_flag = msgQuque->send_flag;

	if (msgsnd(msgId, msg, sndTextLen, send_flag) == -1) {
	
		perror("msgsnd error\n");
		return -1;
	}

	return 0;
}

int ipcMsg_recv(struct ipc_msg *msgQuque) {
	int msgId = msgQuque->msgId;
	struct msgbuf* msg = msgQuque->rcvbuf;
	size_t rcvTextLen = msgQuque->rcvTextLen;
	long mtype = msg->mtype;
	int recv_flag = msgQuque->recv_flag;

	if (msgrcv(msgId, msg, rcvTextLen, mtype, recv_flag)==-1) {
	
		perror("msgrcv error\n");
		return -1;
	}

	return 0;
}

int ipcMsg_init(struct ipc_msg *msgQuque, const char *file, const char c) {

	key_t key;
	int msgId;

	//系统建立IPC通讯 （消息队列、信号量和共享内存） 时必须指定一个ID值。通常情况下，该id值通过ftok函数得
	key = ftok(file, c);
	if (key<0) {
	
		perror("get ipc msg key error ... \n");
		return -1;
	}

	printf("get ipc msg key %d ... \n", key);

	//用来创建和访问一个消息队列
	msgId = msgget(key, IPC_CREAT |IPC_EXCL|0666); //通过文件对应

	if (msgId==-1) {
		if (errno == EEXIST)
		{
			printf("EEXIST:.....\n");
			key=ftok(file, c);
			msgId=msgget(key, IPC_CREAT|0666); //通过文件对应
		}
		else
		{
			perror("msget error ... \n");
			return -1;
		}
	}

	printf("msgid:%d \n", msgId);
	msgQuque->msgId = msgId;

	return 0;
}

