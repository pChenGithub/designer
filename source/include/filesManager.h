
#ifndef _FILESMANAGER_H_
#define _FILESMANAGER_H_
#include "fileTools.h"
#include "common.h"
#include "runTime.h"
struct filesManager {
	char runtime_log[16];
	char file_path[16];
	char up_url[128];
	char url[128];
	char update_ing;
	char upload_file;
	struct current_time current_file; /* offline msg file */
	struct runTime* rt;
	void (*offline_msg_catEND)(struct filesManager* fm);
	void (*store_offline_msg)(struct filesManager* fm, char* msg);
	void (*upload_offline_msg)(struct filesManager* fm);
	void (*store_runtime_log)(void );
	void (*download_img)(struct filesManager* fm);
};

void fM_init(struct filesManager* fm);
void fM_offline_msg_catEND(struct filesManager* fm);
void fM_store_offline_msg(struct filesManager* fm, char* msg);
void fM_upload_offline_msg(struct filesManager* fm);
void fM_store_runtime_log();
void fM_download_img(struct filesManager* fm);

#define FILESMANAGER_INIT(fm, runTime) { \
	struct filesManager* p = &fm; \
	p->rt = &runTime; \
	p->offline_msg_catEND = fM_offline_msg_catEND; \
	p->store_offline_msg = fM_store_offline_msg; \
	p->upload_offline_msg = fM_upload_offline_msg; \
	p->store_runtime_log = fM_store_runtime_log; \
	p->download_img = fM_download_img; \
} \

#endif



