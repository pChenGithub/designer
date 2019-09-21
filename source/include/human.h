
#ifndef _HUMAN_H_
#define _HUMAN_H_
#include "listNode.h"
#include <stdio.h>
#include <string.h>
struct human {
	struct node node;
	char name[16];
	struct humansManager* hM;
	void (*human_init)(struct human*);
	void (*check_event)(void);
	void (*hand_event)(void);
	char* pri;
};

#define HUMAN_INIT(h_name) ({ \
	struct human* human = malloc(sizeof(struct human)); \
	printf("human name %s \n", #h_name); \
	memcpy(human->name, #h_name, strlen(#h_name)+1); \
	human->check_event = h_name##_check_event; \
	human->hand_event = h_name##_hand_event; \
	human->human_init = h_name##_human_init; \
	human = human+0; \
})\

#endif
