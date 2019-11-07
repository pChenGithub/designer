
#include "producersManager.h"
#include "producers/quzhou.h"
#include "producers/zheda_sht.h"
#include <stdlib.h>
char pM_check_producer(struct producersManager* pm) {
#if 1
	char tmp[17];
	char swt;
	struct producer* pro;
	NVRamRead("producer", tmp, 16);
	tmp[16] = '\0';
	printf("producer %s \n", tmp);
//	if (tmp[0]=='0')
//		return -1;

	swt = (tmp[0]-'0')*10+tmp[1]-'0';
	pro = (struct producer*)malloc(sizeof(struct producer));
	switch(swt) {
	case PRO_QUZHOU:
		PRO_INIT(pro, quzhou);
		pro->type = PRO_QUZHOU;
		break;
	case PRO_THERMO:
		break;
	case PRO_ZHEDA:
		break;
	case PRO_SGS:
		break;
	case PRO_GUOHE:
		break;
	case PRO_ZHEDA_SHT:
		PRO_INIT(pro, zheda_sht);
		pro->type = PRO_ZHEDA_SHT;
		break;
	default:
		break;
	}
	pm->pro = pro;
	pro->pm = pm;

	return 0;
#endif
}

char pM_init_producer(struct producersManager* pm) {
	struct producer* p = pm->pro;
	if (!p)
		return -1;
	p->init(p);
	return 0;
}


