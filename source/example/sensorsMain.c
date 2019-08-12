/*************************************************************************
	> File Name: sensorsMain.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月12日 星期一 13时04分36秒
 ************************************************************************/

#include <stdio.h>
#include "sensorsManager.h"

struct sensorsManager sensorsManager;
struct ipc_msg ipc_msg;

int main(int argc, char* argv[]) {

	struct sensor* sensor=NULL;

	sensorsManager.ipc = &ipc_msg;
	SENSORSMANAGER_INIT(sensorsManager);
	IPCSMG_INIT(ipc_msg);

	sensor = SENSOR_INIT(vol);
	sM_add_sensor(&sensorsManager, sensor);
	sensor = SENSOR_INIT(rfid);
	sM_add_sensor(&sensorsManager, sensor);

	while(1) {

		sM_foreach_sensors(&sensorsManager);
	}

	return 0;
}


