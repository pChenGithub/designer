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
		mqtt_sync((struct mqtt_client*) client);
		usleep(100000U);
	}
	return NULL;
}

void publish_callback(void** unused, struct mqtt_response_publish *published) 
{
	    /* not used in this example */
	printf("recv msg xxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxxx \n");
}

/*****************************************************************/

void mqtt_tr_send(struct transfer* tr) {
	struct mqtt_tr_pri* p = (struct mqtt_tr_pri*)tr->pri;
	struct mqtt_client* client = & p->client;
	char* msg = p->application_message;
//	struct sensor* sensor = e->sensor;

//	sensor->parse_task(e, tr);

	printf("mqtt send data \n");
//	isprintf(msg, "hello, time is:%s", "12:30");
	mqtt_publish(client, p->topic, msg, strlen(msg) + 1, MQTT_PUBLISH_QOS_0);
}



void mqtt_tr_init(struct transfer* tr) {
	struct mqtt_tr_pri* p;
	int sockfd;
	struct mqtt_client* client;
	p = (struct mqtt_tr_pri*)malloc(sizeof(struct mqtt_tr_pri));
	tr->pri =(char*) p;
	client = & p->client;

	sprintf(p->addr, "%s", "40.73.40.164");
	sprintf(p->port, "%s", "11883");
	sprintf(p->topic, "%s", "datetime");

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

	pthread_t client_daemon;
	if(pthread_create(&client_daemon, NULL, client_refresher, client)) {
		fprintf(stderr, "Failed to start client daemon.\n");
		exit_example(EXIT_FAILURE, sockfd, NULL);
	}

	printf("ready to begin publishing the time.\n");
}




