/*************************************************************************
	> File Name: sensorsManager.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月12日 星期一 12时38分17秒
 ************************************************************************/

#include "sensorsManager.h"
#include "listNode.h"

static void sM_sync_event(struct sensorsManager* sM) {

	/*msg ipc send */
	ipcMsg_send(sM->ipc);
//	sleep(1);
}

int sM_foreach_sensors(struct sensorsManager* sM) {

	struct node* node = sM->s_list;
	char count = sM->s_count;
	int delay = sM->freq;
	struct sensor* sensor;

	if (!count) {
		perror("sensors list is empty \n");
		return -1;
	}

	printf("sensor count %d \n", count);

	while (count--) {
		sensor = (struct sensor*)node;
	//	printf("a sensor, do task \n");
//		s_task();

		printf("sensor name %s \n", sensor->name);
		sensor->readData_task(sensor->pri);
		sM_sync_event(sM);

		node = node->next;
	}

	printf("delay %d us \n", delay);
	usleep(delay);

	return 0;
}

int sM_add_sensor(struct sensorsManager* sM, struct sensor* sensor) {

	char* count = & sM->s_count;
	struct node* p = (struct node*)sensor;

	if (*count==0) {
		sM->s_list = p;
		insert_first(p);
	}else {
		insert(sM->s_list->pre, p);
	}

	sensor->sM = sM;
	sensor->sensor_init(sensor->pri, sensor);

	(*count) ++;

	return 0;
}




