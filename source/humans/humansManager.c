/*************************************************************************
	> File Name: humansManager.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月13日 星期二 16时18分05秒
 ************************************************************************/

#include <stdio.h>
#include "humansManager.h"

int hM_add_human(struct humansManager* hM, struct human* human) {

	char* count = & hM->h_count;
	struct node* p = (struct node*)human;

	printf("add human \n");
	if (*count==0) {
		hM->h_list = p;
		insert_first(p);
	} else {
		insert(hM->h_list->pre, p);
	}

	human->hM = hM;
	human->human_init(human);

	(*count)++;

	return 0;
}

int hM_select_humans(struct humansManager* hM) {
	struct node* node = hM->h_list;
	char count = hM->h_count;
	int delay = hM->freq;
	struct human* human;

//	printf("check humans \n");
	if (!count) {
		perror("humans list is empty \n");
		return -1;
	}

//	printf("human count %d \n", count);

	while(count--) {
		human = (struct human*)node;
//		printf("human Name %s \n", human->name);
		human->check_event(human);
		human->hand_event(human);
		node = node->next;
	}

	usleep(delay);
}

void hM_del_human() {}

void hM_init() {}



