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

void hM_select_humans() {

	printf("check humans \n");
	sleep(1);
}

void hM_del_human() {}

void hM_init() {}



