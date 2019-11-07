
#ifndef _PRODUCTORSMANAGER_H_
#define _PRODUCTORSMANAGER_H_
#include "producer.h"
#include "runTime.h"
struct producersManager {
	struct producer* pro;
	struct runTime* rt;
	char (*check_producer)(struct producersManager* pm);
	char (*init_producer)(struct producersManager* pm);
};

char pM_check_producer(struct producersManager* pm);
char pM_init_producer(struct producersManager* pm);

#define PRODUCERSMANAGER_INIT(pm, runTime) { \
	struct producersManager* p = & pm; \
	p->pro = NULL; \
	p->rt = &runTime; \
	p->check_producer = pM_check_producer; \
	p->init_producer = pM_init_producer; \
}\

#endif


