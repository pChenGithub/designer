/*************************************************************************
	> File Name: mqtt_tr.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月20日 星期二 10时33分10秒
 ************************************************************************/

#include <string.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "mqtt_tr.h"
#include "mqtt.h"
#include "templates/posix_sockets.h"
#include "sensor.h"
#include "runTime.h"
#include "transfersManager.h"
#include "filesManager.h"

void publish_callback(struct mqtt_client* client, void** unused, struct mqtt_response_publish *published) 
{
	    /* not used in this example */
//	printf("recv msg xxxxxxxxxxxxxxxxxx 123 xxxxxxxxxxxxxxxxx \n");
	char* topic_name = (char*) malloc(published->topic_name_size+1);
//	char* msg = (char*) malloc(published->application_message_size+1);
//	struct mqtt_msg_rcv* msg_format = (struct mqtt_tr_recv*) malloc(sizeof(struct mqtt_msg_rcv));
	memcpy(topic_name, published->topic_name, published->topic_name_size);
//	memcpy(msg, published->application_message, published->application_message_size);
	topic_name[published->topic_name_size] = '\0';
	char* msg = client->rcv_msg;
	memcpy(msg, published->application_message, published->application_message_size);
	msg[published->application_message_size] = '\0';

	printf("topic: %s, msg %s \n", topic_name, msg);
	free(topic_name);
}

/*****************************************************************/

void mqtt_tr_send(struct transfer* tr) {
	struct mqtt_tr_pri* p = (struct mqtt_tr_pri*)tr->pri;
	struct mqtt_client* client = & p->client;
	char* msg = p->application_message;
	struct runTime_object* obj = & tr->tm->rt->object;
	struct filesManager* fm = obj->fm;

	printf("mqtt send data \n");
//	isprintf(msg, "hello, time is:%s", "12:30");
	mqtt_publish(client, p->topic, msg, strlen(msg), MQTT_PUBLISH_QOS_0);
	if (client->error != MQTT_OK) {
		fprintf(stderr, "error: %s\n", mqtt_error_str(client->error));
		fm->store_runtime_log(fm, "mqtt publish error");
	}
}

void mqtt_tr_recv(struct transfer* tr, char* buf) {
	struct mqtt_tr_pri* p = (struct mqtt_tr_pri*)tr->pri;
	struct mqtt_client* client = & p->client;
	client->rcv_msg = buf; //len 128 no check
	mqtt_sync(client);
}

void mqtt_tr_init(struct transfer* tr) {
	struct mqtt_tr_pri* p;
	int sockfd;
	struct mqtt_client* client;
	char serviceip[32];
	char i=0;
	struct runTime_object* obj = & tr->tm->rt->object;
	struct filesManager* fm = obj->fm;

	p = (struct mqtt_tr_pri*)malloc(sizeof(struct mqtt_tr_pri));
	memset(p, 0, sizeof(struct mqtt_tr_pri));

	tr->pri =(char*) p;
	client = & p->client;

	mfg_read_server_ip(serviceip, 32);
	while(i<32) {
		if (serviceip[i]==':') {
			serviceip[i] = '\0';
			break;
		}
		i++;
	}

	//sprintf(p->addr, "%s", "40.73.40.164");
	sprintf(p->addr, "%s", serviceip);
	sprintf(p->port, "%s", serviceip+i+1);

	mfg_read_sn(p->sn, 18);
	p->sn[18] = '\0';
	//sprintf(p->topic, "%s", "msg2client");
	sprintf(p->topic, "%s/%s", "/InteDev/group1", p->sn);
	sprintf(p->sub_topic, "%s/%s", p->topic, "setting");

	sockfd = open_nb_socket(p->addr, p->port);
	if (sockfd == -1) {
		perror("Failed to open socket: ");
		fm->store_runtime_log(fm, "mqtt socket error");
		return ;
	}

//	printf("sizeof(p->sendbuf) %d, \n ", sizeof(p->sendbuf));
	mqtt_init(client, sockfd, p->sendbuf, sizeof(p->sendbuf), p->recvbuf, sizeof(p->recvbuf), publish_callback);
	mqtt_connect(client, p->sn, NULL, NULL, 0, NULL, NULL, 0, 5);
	if (client->error != MQTT_OK) {
		fprintf(stderr, "error: %s\n", mqtt_error_str(client->error));
		fm->store_runtime_log(fm, "mqtt connect error");
		close(sockfd);
		return ;
	}
	mqtt_subscribe(client, p->sub_topic, 0);
	printf("ready to begin publishing the time.\n");
	sleep(3);
}

void mqtt_tr_reconnect(struct transfer* tr) {
	struct mqtt_tr_pri* p = (struct mqtt_tr_pri*)tr->pri;
	struct runTime_object* obj = & tr->tm->rt->object;
	struct filesManager* fm = obj->fm;
	int sockfd;
	struct mqtt_client* client = & p->client;

	printf("mqtt reconnect ... \n");
	fm->store_runtime_log(fm, "mqtt reconnect ...");
	while(1) {
		sockfd = open_nb_socket(p->addr, p->port);
		if (sockfd == -1) {
			perror("Failed to open socket: ");
			fm->store_runtime_log(fm, "mqtt re socket error");
			continue;
		}
		mqtt_init(client, sockfd, p->sendbuf, sizeof(p->sendbuf), p->recvbuf, sizeof(p->recvbuf), publish_callback);
		mqtt_connect(client, p->sn, NULL, NULL, 0, NULL, NULL, 0, 5);
		if (client->error != MQTT_OK) {
			fprintf(stderr, "error: %s\n", mqtt_error_str(client->error));
			fm->store_runtime_log(fm, "mqtt re connect error");
			close(sockfd);
			sleep(3);
			continue;
		}
		mqtt_subscribe(client, p->sub_topic, 0);
		sleep(3);
		fm->store_runtime_log(fm, "mqtt reconnect done");
		printf("mqtt reconnect done \n");
		break;
	}
}



