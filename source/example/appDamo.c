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
#include "filesManager.h"
#include "eventsManager.h"
#include "producersManager.h"
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
static struct filesManager filesManager;
static struct producersManager producersManager;

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
	obj->fm = & filesManager;
	obj->prom = & producersManager;

	task = obj->task_product;
	task->init(task, PRODUCT);
	task = obj->task_wait_event;
	task->init(task, WAIT_EVENT);
	//task->start(task);

	FILESMANAGER_INIT(filesManager, runTime);
	fM_init(obj->fm);

/* sensorsManager */
	SENSORSMANAGER_INIT(sensorsManager, runTime);
//	sensor = SENSOR_INIT(pt100);
//	sM_add_sensor(&sensorsManager, sensor);
//	sensor = SENSOR_INIT(press303);
//	sM_add_sensor(&sensorsManager, sensor);
#if 1
/* transfersManager */
#if 1
	TRANSFERSMANAGER_INIT(transfersManager);
	tM_init(&transfersManager);
#endif

/* humansManager */
#if 1
	HUMANSMANAGER_INIT(humansManager, runTime);
	human = HUMAN_INIT(mqtt);
	hM_add_human(&humansManager, human);
#endif
#if 1
	PRODUCERSMANAGER_INIT(producersManager, runTime);
	if (producersManager.check_producer(&producersManager) <0) {
		perror("has no env producer \n");
		return -1;
	}
	producersManager.init_producer(&producersManager);
#endif

	task->start(obj->task_product);
	task->start(obj->task_wait_event);
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





