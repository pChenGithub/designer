
#include "runTime.h"
#include "transfersManager.h"
#include "pthread_task_com.h"

void rT_check_state(struct runTime* rT) {
	char tmp = 1;
	enum net_state state;
	struct transfer* tr;
	struct pthread_task_com* task;
	struct runTime_object* obj = & rT->object;
	if (system("ping 223.6.6.6 -c 1 -W 1"))
		if (system("ping 223.6.6.6 -c 1 -W 1"))
			tmp = 0;
	state = tmp?ONLINE:OFFLINE;
	if (rT->n_state != state && !state) {
		/* net reconnetc */
		printf("notice: online \n");
		tr = obj->tm->select;
		tr->transfer_reconnect(tr);
		task = obj->task_product;
		task->state_switch(task, 0);
		task = obj->task_wait_event;
		task->state_switch(task, 0);
		rT->n_state = state;
	} else if (rT->n_state != state) { /* disconnetc */
		printf("notice: offline \n");
		task = obj->task_product;
		task->state_switch(task, 1);
		task = obj->task_wait_event;
		task->state_switch(task, 1);
		rT->n_state = state;
	}
}

void rT_check_runTime_env(struct runTime* rt) {
	printf("ENTER: %s \n", __func__ );
}

void rT_offline_runtime() {

}

void rT_online_runtime() {

}
