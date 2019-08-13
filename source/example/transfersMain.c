/*************************************************************************
	> File Name: transfersMain.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月13日 星期二 17时21分42秒
 ************************************************************************/

#include <stdio.h>
#include "transfersManager.h"
#include "ipc.h"

struct transfersManager transfersManager;
struct ipc_msg ipc_msg;

int main(int argc, char* argv[] ) {

	transfersManager.ipc = &ipc_msg;
	TRANSFERSMANAGER_INIT(transfersManager);
	IPCSMG_INIT(ipc_msg);

	transfersManager.mode = MQTT;

	while(1) {
	
		tM_hand_msg();
	}

	return 0;
}
