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
#include "pthread_task_com.h"

static struct runTime runTime;
static struct sensorsManager sensorsManager;
static struct humansManager humansManager;
static struct transfersManager transfersManager;
static struct eventsManager eventsManager;
static struct pthread_task_com task_product;
static struct pthread_task_com task_wait_event;

int main(int argc, char* argv[] ) {

	struct sensor* sensor;
	struct human* human;
	pthread_t pid;

	EVENTSMANAGER_INIT(eventsManager);
	eM_init(&eventsManager);

/* sensorsManager */
	sensorsManager.eM = & eventsManager;
	SENSORSMANAGER_INIT(sensorsManager);

	sensor = SENSOR_INIT(pt100);
	sM_add_sensor(&sensorsManager, sensor);
	sensor = SENSOR_INIT(press303);
	sM_add_sensor(&sensorsManager, sensor);
#if 0
	sensor = SENSOR_INIT(vol);
	sM_add_sensor(&sensorsManager, sensor);
	sensor = SENSOR_INIT(rfid);
	sM_add_sensor(&sensorsManager, sensor);
#endif

#if 0
	pthread_create(&pid, NULL, sM_pthread_read, &sensorsManager);
	pthread_detach(pid);
#endif
/**/
#if 1
/* transfersManager */
#if 1
	transfersManager.eM = &eventsManager;
	transfersManager.sM = &sensorsManager;
	TRANSFERSMANAGER_INIT(transfersManager);
	tM_init(&transfersManager);
#endif
#if 0
	pthread_create(&pid, NULL, tM_pthread_hand_event, &transfersManager);
	pthread_detach(pid);
#endif
#if 1
	task_product.sM = &sensorsManager;
	task_product.tM = &transfersManager;
	pT_init(&task_product, PRODUCT);
#endif

#if 0
	HUMANSMANAGER_INIT(humansManager);
	human = HUMAN_INIT(mqtt);
	hM_add_human(&humansManager, human);

	task_product.hM = &humansManager;
	task_product.tM = &transfersManager;
	pT_init(&task_wait_event, WAIT_EVENT);
#endif

/**/
#endif
	while(1)
		sleep(60);

	return 0;
}





