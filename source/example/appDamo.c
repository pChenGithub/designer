/*************************************************************************
	> File Name: appDamo.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月14日 星期三 13时33分57秒
 ************************************************************************/

#include <stdio.h>
#include <pthread.h>
#include "sensorsManager.h"
#include "humansManager.h"
#include "transfersManager.h"
#include "eventsManager.h"
#include "vol.h"
#include "rfid.h"
#include "runTime.h"

static struct runTime runTime;
static struct ipc_msg ipc_msg;
static struct sensorsManager sensorsManager;
static struct humansManager humansManager;
static struct transfersManager transfersManager;
static struct eventsManager eventsManager;

int main(int argc, char* argv[] ) {

	struct sensor* sensor;
	pthread_t pid;

	EVENTSMANAGER_INIT(eventsManager);
	eM_init(&eventsManager);

/* sensorsManager */
	sensorsManager.ipc = &ipc_msg;
	sensorsManager.eM = & eventsManager;
	SENSORSMANAGER_INIT(sensorsManager);
	IPCSMG_INIT(ipc_msg);

	sensor = SENSOR_INIT(vol);
	sM_add_sensor(&sensorsManager, sensor);
	sensor = SENSOR_INIT(rfid);
	sM_add_sensor(&sensorsManager, sensor);

	pthread_create(&pid, NULL, sM_pthread_read, &sensorsManager);
	pthread_detach(pid);
/**/

/* transfersManager */
	transfersManager.eM = &eventsManager;
	TRANSFERSMANAGER_INIT(transfersManager);
	tM_init(&transfersManager);

	pthread_create(&pid, NULL, tM_pthread_hand_event, &transfersManager);
	pthread_detach(pid);
/**/

	while(1)
		sleep(10);

	return 0;
}





