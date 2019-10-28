
#include <time.h>
#include "runTime.h"
#include "transfersManager.h"
#include "pthread_task_com.h"
#include "filesManager.h"

void rT_update_switch_time(struct runTime* rt) {
	time_t t;
	struct tm* tm_info;
	struct current_time* p = & rt->t;
	t = time(NULL);
	tm_info = localtime(&t);
	p->mon = tm_info->tm_mon+1;
	p->day = tm_info->tm_mday;
	p->hour = tm_info->tm_hour;
	p->min = tm_info->tm_min;
}

void rT_check_state(struct runTime* rT) {
	char tmp = 1;
	enum net_state state;
	struct transfer* tr;
	struct pthread_task_com* task;
	struct runTime_object* obj = & rT->object;
	struct filesManager* fm = obj->fm;
	if (system("ping 223.6.6.6 -c 2 -W 2")) {
		sleep(3);
		if (system("ping 223.5.5.5 -c 2 -W 2"))
			tmp = 0;
	}
	state = tmp?ONLINE:OFFLINE;
	if (rT->n_state != state && !state) {
		/* net reconnect */
		printf("notice: online \n");
		rT->update_state_switch_time(rT);
		rT->n_state = state;
		tr = obj->tm->select;
		sleep(1);
		tr->transfer_reconnect(tr);
		sleep(1);
		task = obj->task_product;
		task->state_switch(task, 0);
		task = obj->task_wait_event;
		task->state_switch(task, 0);
		fm->offline_msg_catEND(fm);
		fm->upload_offline_msg(fm);
	} else if (rT->n_state != state) { /* disconnect */
		printf("notice: offline \n");
		rT->update_state_switch_time(rT);
		rT->n_state = state;
		fm->current_file = rT->t;
		task = obj->task_product;
		task->state_switch(task, 1);
		task = obj->task_wait_event;
		task->state_switch(task, 1);
	}
}

void rT_check_runTime_env(struct runTime* rt) {
	printf("ENTER: %s \n", __func__ );
	/* online */
	while (system("ping 223.6.6.6 -c 2 -W 2"))
		sleep(3);
	/* net time */
	/* sn */
	mfg_read_sn(rt->sn, 18);
	rt->sn[18] = '\0';
}

void rT_offline_runtime() {

}

void rT_online_runtime() {

}
