/*************************************************************************
	> File Name: event/eventsManager.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月14日 星期三 14时53分57秒
 ************************************************************************/

#include <stdio.h>
#include "eventsManager.h"

int eM_add_event(struct eventsManager* eM, struct event* event) {
	char* count = & eM->e_count;
	struct node* p = (struct node*)event;

	printf("event count %d \n", *count);

	if (*count==0) {
		eM->e_list = p;
		insert_first(p);
	}else {
		insert(eM->e_list->pre, p);
	}

	event->eM = eM;

	(*count) ++;

	return 0;
}

int eM_del_event(struct eventsManager* eM, struct event* event) {
	char* count = & eM->e_count;
	struct node* p = (struct node*)event;

	if (*count==0) {
		printf("list empty \n");
		return -1;
	}else if (*count==1) {
		eM->e_list = NULL;
	}else {
		remove_node(p);
		eM->e_list = p->next;
	}

	(*count) --;

}
