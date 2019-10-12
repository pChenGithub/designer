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

#include "humans/human_mqtt.h"

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
	struct runTime_object* obj;
	struct pthread_task_com* task;

	RUNTIME_INIT(runTime);
	PTHREAD_TASK_INIT(task_product, runTime);
	PTHREAD_TASK_INIT(task_wait_event, runTime);

	runTime.check_env(&runTime);

	obj = &runTime.object;
	obj->sm = &sensorsManager;
	obj->hm = &humansManager;
	obj->tm = &transfersManager;
	obj->task_product = &task_product;
	obj->task_wait_event = & task_wait_event;

	task = obj->task_product;

	task->init(task, PRODUCT);
	task->start(task);






/* sensorsManager */
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

#if 1
	humansManager.tM = &transfersManager;
	HUMANSMANAGER_INIT(humansManager);
	human = HUMAN_INIT(mqtt);
	hM_add_human(&humansManager, human);

	task_wait_event.hM = &humansManager;
	task_wait_event.tM = &transfersManager;
	pT_init(&task_wait_event, WAIT_EVENT);
#endif

/**/
#endif
	printf("check runTime env \n");
	while(1) {
		/* net state */
		runTime.check_state(&runTime);
		sleep(10);
	}

	return 0;
}





