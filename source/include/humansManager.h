/*************************************************************************
	> File Name: humansManager.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年08月13日 星期二 16时18分30秒
 ************************************************************************/

#ifndef _HUMANSMANAGER_H_
#define _HUMANSMANAGER_H_
#include "human.h"
#include "humans/human_mqtt.h"

struct humansManager {
	int freq;
	char h_count;
	struct node* h_list;
	void (*wait_event)(void);
	struct transfersManager* tM;
};

void hM_init(void);
void hM_select_humans(void);
int hM_add_human(struct humansManager* hM, struct human* human);
void hM_del_hunam(void);

#define HUMANSMANAGER_INIT(name) {\
	struct humansManager* p = &name; \
	p->freq = 100000; \
	p->h_count = 0; \
	p->h_list = NULL; \
	p->wait_event = hM_select_humans; \
} \


#endif




