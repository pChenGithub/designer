
#ifndef _PRODUCER_H_
#define _PRODUCER_H_
enum pro_type {
	xxx,
	PRO_QUZHOU,
	PRO_THERMO,
	PRO_ZHEDA,
	PRO_SGS,
	PRO_GUOHE,
	PRO_ZHEDA_SHT,
};

struct producer {
	enum pro_type type;
	char name[16];
	struct producersManager* pm;
	void (*init)(struct producer* pro);
};

#define PRO_INIT(p, typ) { \
	memcpy(p->name, #typ, strlen(#typ)+1); \
	p->init = typ##_pro_init; \
}\


#endif

