/*************************************************************************
	> File Name: mqtt_tr.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月20日 星期二 10时33分10秒
 ************************************************************************/

#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include "mqtt_tr.h"
#include "mqtt.h"
#include "templates/posix_sockets.h"
#include "sensor.h"

void exit_example(int status, int sockfd, pthread_t *client_daemon)
{
	if (sockfd != -1) close(sockfd);
	if (client_daemon != NULL) pthread_cancel(*client_daemon);
	exit(status);
}

void* client_refresher(void* client)
{
	while(1) 
	{
//		printf("sync %d\n", mqtt_sync((struct mqtt_client*) client));
		mqtt_sync_recv((struct mqtt_client*) client);
		usleep(100000U);
	}
	return NULL;
}

void publish_callback(void** unused, struct mqtt_response_publish *published) 
{
	    /* not used in this example */
	printf("recv msg xxxxxxxxxxxxxxxxxx 123 xxxxxxxxxxxxxxxxx \n");
	char* topic_name = (char*) malloc(published->topic_name_size+1);
	char* msg = (char*) malloc(published->application_message_size+1);
	memcpy(topic_name, published->topic_name, published->topic_name_size);
	memcpy(msg, published->application_message, published->application_message_size);

	topic_name[published->topic_name_size] = '\0';
	msg[published->application_message_size] = '\0';

	printf("topic: %s, msg %s \n", topic_name, msg);

	free(topic_name);
	free(msg);
}

/*****************************************************************/

void mqtt_tr_send(struct transfer* tr) {
	struct mqtt_tr_pri* p = (struct mqtt_tr_pri*)tr->pri;
	struct mqtt_client* client = & p->client;
	char* msg = p->application_message;
	char flag = 6;
//	struct sensor* sensor = e->sensor;

//	sensor->parse_task(e, tr);

	printf("mqtt send data \n");
//	isprintf(msg, "hello, time is:%s", "12:30");
	mqtt_publish(client, p->topic, msg, strlen(msg) + 1, MQTT_PUBLISH_QOS_0);
//	printf("mqtt send sync \n");
//	while(flag--) {
//		mqtt_sync_send(client);
//		usleep(100000);
//	}

}

void mqtt_tr_recv(struct transfer* tr) {
	struct mqtt_tr_pri* p = (struct mqtt_tr_pri*)tr->pri;
	struct mqtt_client* client = & p->client;
	mqtt_sync(client);
}

void mqtt_tr_init(struct transfer* tr) {
	struct mqtt_tr_pri* p;
	int sockfd;
	struct mqtt_client* client;
	p = (struct mqtt_tr_pri*)malloc(sizeof(struct mqtt_tr_pri));

	memset(p, 0, sizeof(struct mqtt_tr_pri));

	tr->pri =(char*) p;
	client = & p->client;

	sprintf(p->addr, "%s", "40.73.40.164");
	sprintf(p->port, "%s", "11883");
	sprintf(p->topic, "%s", "msg2client");

	sockfd = open_nb_socket(p->addr, p->port);
	if (sockfd == -1) {
		perror("Failed to open socket: ");
		exit_example(EXIT_FAILURE, sockfd, NULL);
	}

//	printf("sizeof(p->sendbuf) %d, \n ", sizeof(p->sendbuf));

	mqtt_init(client, sockfd, p->sendbuf, sizeof(p->sendbuf), p->recvbuf, sizeof(p->recvbuf), publish_callback);
	mqtt_connect(client, "publishing_clientxxxxxxx", NULL, NULL, 0, NULL, NULL, 0, 5);
	if (client->error != MQTT_OK) {
		fprintf(stderr, "error: %s\n", mqtt_error_str(client->error));
		exit_example(EXIT_FAILURE, sockfd, NULL);
	}
#if 0
	pthread_t client_daemon;
	if(pthread_create(&client_daemon, NULL, client_refresher, client)) {
		fprintf(stderr, "Failed to start client daemon.\n");
		exit_example(EXIT_FAILURE, sockfd, NULL);
	}
#endif
	mqtt_subscribe(client, "appdemotest", 0);
	printf("ready to begin publishing the time.\n");
}

void mqtt_tr_reconnect(struct transfer* tr) {
	struct mqtt_tr_pri* p = (struct mqtt_tr_pri*)tr->pri;
	int sockfd;
	struct mqtt_client* client = & p->client;
	sockfd = open_nb_socket(p->addr, p->port);
	if (sockfd == -1) {
		perror("Failed to open socket: ");
		exit_example(EXIT_FAILURE, sockfd, NULL);
	}

//	printf("sizeof(p->sendbuf) %d, \n ", sizeof(p->sendbuf));

	mqtt_init(client, sockfd, p->sendbuf, sizeof(p->sendbuf), p->recvbuf, sizeof(p->recvbuf), publish_callback);
	mqtt_connect(client, "publishing_clientxxxxxxx", NULL, NULL, 0, NULL, NULL, 0, 5);
	if (client->error != MQTT_OK) {
		fprintf(stderr, "error: %s\n", mqtt_error_str(client->error));
		exit_example(EXIT_FAILURE, sockfd, NULL);
	}
}



