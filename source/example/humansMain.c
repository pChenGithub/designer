/*************************************************************************
	> File Name: humansMain.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月13日 星期二 16时35分35秒
 ************************************************************************/

#include <stdio.h>
#include "humansManager.h"

static struct humansManager humansManager;
static struct ipc_msg ipc_msg;

int main(int argc, char* argv[]) {

	humansManager.ipc = &ipc_msg;
	SENSORSMANAGER_INIT(humansManager);
	IPCSMG_INIT(ipc_msg);

	while(1) {

		hM_slect_humans();
	}

	return 0;
}




