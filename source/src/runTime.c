
#include "runTime.h"
#include "transfersManager.h"

void rT_check_state(struct runTime* rT) {
	char tmp = 1;
	enum net_state state;
	struct transfer* tr;
	if (system("ping 223.6.6.6 -c 1 -W 1"))
		if (system("ping 223.6.6.6 -c 1 -W 1"))
			tmp = 0;
	state = tmp?ONLINE:OFFLINE;
	if (rT->n_state != state && !state) {
		/* net reconnetc */
		printf("notice: online \n");
		tr = rT->tM->select;
		tr->transfer_reconnect(tr);
		rT->n_state = state;
	} else if (rT->n_state != state) { /* disconnetc */
		printf("notice: offline \n");
		rT->n_state = state;
	}
}

void rT_check_runTime_env() {
	printf("ENTER: %s \n", __func__ );
}

void rT_offline_runtime() {

}

void rT_online_runtime() {

}
