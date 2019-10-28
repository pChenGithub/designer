
#include "humans/human_mqtt.h"
#include "humansManager.h"
#include "runTime.h"
#include "mqtt_tr.h"
#include "filesManager.h"
#include "runTime.h"
#include "../MSGService/MSGService.h"

void mqtt_human_init(struct human* human) {
	struct human_mqtt_pri* pri;
	struct runTime_object* obj = & human->hM->rt->object;
	printf("mqtt human init \n");
	human->pri = malloc(sizeof(struct human_mqtt_pri));
	pri = (struct human_mqtt_pri*)human->pri;
	pri->tr = obj->tm->select;
	printf("mqtt human init done \n");
}


int str_to_int(const char* str, char len) {

	int ret=0;
	char i;

	for (i=0;i<len;i++) {
		ret = ret*10+str[i]-48;
	}

	return ret;
}

int str_to_format(struct mqtt_msg_rcv* msg_format, const char* msg) {

	printf("msg: %s \n", msg);
	char i,j;
	char len;
	char cut_pos[3]; //+ + :
	char n;

	const char* p;

	len = strlen(msg);
	j=0;

	for (i=0;i<len;i++) {
		if (msg[i]=='+') {
			cut_pos[j] = i;
			j++;
		}
	}

//	printf("+ pos %d %d \n", cut_pos[0], cut_pos[1]);

	p = msg+cut_pos[0]+1;
	n = cut_pos[1]-cut_pos[0];
	for (i=0;i<n;i++) {
		if (p[i]==':') {
			cut_pos[j] = i+cut_pos[0]+1;
			break;
		}
	}
//	printf(": pos %d \n", cut_pos[2]);

	memset(msg_format, 0, sizeof(struct mqtt_msg_rcv));
//	printf("str len %d \n", len);

	msg_format->len = str_to_int(msg, cut_pos[0]);
	msg_format->uuid = str_to_int(msg+cut_pos[1]+1, len-1-cut_pos[1]);
	memcpy(msg_format->event, msg+cut_pos[0]+1, cut_pos[2]-cut_pos[0]-1);
	memcpy(msg_format->pri_dat, msg+cut_pos[2]+1, cut_pos[1]-cut_pos[2]-1);

	return 0;
}

char check_serviceip(char* serviceip) {

	return 0;
}

void mqtt_hand_event(struct human* human) {
	struct human_mqtt_pri* pri = (struct human_mqtt_pri*)human->pri;
	struct transfer* tr = pri->tr;
	struct mqtt_msg_rcv* msg_format = & pri->msg_format;
	struct mqtt_tr_pri* tr_pri = (struct mqtt_tr_pri*)tr->pri;
	char* msg = tr_pri->application_message;
	pthread_mutex_t* lock_send_msg = & tr_pri->lock_send_msg;
	struct runTime_object* obj = & human->hM->rt->object;
	struct filesManager* fm = obj->fm;

	if (!strncmp(msg_format->event, "upgrade", 7)) {
		if (! fm->update_ing) {
			fm->update_ing = 1;
			memcpy(fm->url, msg_format->pri_dat, 128);
			fm->download_img(fm);
		}
	}else if (!strncmp(msg_format->event, "bezero", 6)) {
		mfg_write_drift_to_zero(msg_format->pri_dat);
	}else if (!strncmp(msg_format->event, "quebezero", 6)) {
		float tmp;
		tmp = mfg_read_drift_to_zero();
		pthread_mutex_lock(lock_send_msg);
		sprintf(msg, "bezero: %.02f", tmp);
		tr->send_data(tr);
		pthread_mutex_unlock(lock_send_msg);
	}else if (!strncmp(msg_format->event, "threshold", 9)) {
		NVRamWrite("threshold", msg_format->pri_dat);
	}else if (!strncmp(msg_format->event, "reboot", 6)) {
		system("reboot");
	}else if (!strncmp(msg_format->event, "version", 7)) {
		pthread_mutex_lock(lock_send_msg);
		//memcpy(msg, "version: 8.8.8.8", 16);
		get_software_version(msg, 16);
		tr->send_data(tr);
		pthread_mutex_unlock(lock_send_msg);
	}else if (!strncmp(msg_format->event, "serviceip", 9)) {
		if (check_serviceip(msg_format->pri_dat) == 0) {
			mfg_write_server_ip(msg_format->pri_dat);
		}
	}else if (!strncmp(msg_format->event, "configfile", 10)) {

	}
}

void mqtt_check_event(struct human* human) {
	struct human_mqtt_pri* pri = (struct human_mqtt_pri*)human->pri;
	struct transfer* tr;
	char* msg = pri->buf;
	struct mqtt_msg_rcv* msg_format = & pri->msg_format;
//	printf("check mqtt recv event \n");
	tr = pri->tr;
	memset(msg, 0, 128);
	tr->recv_data(tr, msg);
	if (msg[0]==0)
		return ;

	str_to_format(msg_format, msg);
	//memset(msg, 0, 128);

	printf("msg len %d \n", msg_format->len);
	printf("msg uuid %d \n", msg_format->uuid);
	printf("msg event %s \n", msg_format->event);
	printf("msg pri_dat %s \n", msg_format->pri_dat);

	mqtt_hand_event(human);
}

