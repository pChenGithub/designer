
#include "filesManager.h"
#include "fileTools.h"
#include "ftpget.h"
#include <time.h>
#include <pthread.h>
#include <dirent.h>
#include <sys/types.h>
#include <stdio.h>

void fM_init(struct filesManager* fm) {
	char* buf;
	buf = fm->file_path;
	sprintf(buf, "%s", "/tmp");
	buf = fm->up_url;
	sprintf(buf, "%s", "ftp://intelab:ZMER%40K+2-Xy7j)Q)0nET@139.219.136.0:8194/monitoring/");
	pthread_mutex_init(&fm->lock_log_file, NULL);
	fm->update_ing = 0;
	fm->upload_file = 0;
}

void fM_offline_msg_catEND(struct filesManager* fm) {
	char file[64];
	struct current_time* current_file = & fm->current_file;
	sprintf(file, "%s/123456789-%02d_%02d_%02d_%02d", fm->file_path, 
			current_file->mon, current_file->day, 
			current_file->hour, current_file->min);
	str_write_to_file(file, "END");
}

void fM_store_offline_msg(struct filesManager* fm, char* msg) {
	char file[64];
	struct current_time* current_file = & fm->current_file;
	struct runTime* rt = fm->rt;
	time_t t;
	struct tm* tm_info;
	t = time(NULL);
	tm_info = localtime(&t);
	if (current_file->hour != tm_info->tm_hour) {
		sprintf(file, "%s/%s-%02d_%02d_%02d_%02d", fm->file_path, rt->sn,
				current_file->mon, current_file->day, 
				current_file->hour, current_file->min);
		str_write_to_file(file, "END");

		current_file->mon = tm_info->tm_mon+1;
		current_file->day = tm_info->tm_mday;
		current_file->hour = tm_info->tm_hour;
		current_file->min = tm_info->tm_min;
	}

	sprintf(file, "%s/%s-%02d_%02d_%02d_%02d", rt->sn, fm->file_path, 
			current_file->mon, current_file->day, 
			current_file->hour, current_file->min);
	str_write_to_file(file, msg);
}

void *upload_offline_file(void* arg) {
	struct filesManager* fm = (struct filesManager*)arg;
	struct runTime* rt = fm->rt;
	int size=0;
	DIR* dir;
	struct dirent* entry;
	char f[64];

	dir = opendir(fm->file_path);
	printf("start upload offline msg \n");
	while((entry=readdir(dir)) && (rt->n_state)==ONLINE ) {
		if (!strncmp(entry->d_name, "086021060", 9)) {
			size = ftp_upload_file(fm->up_url, fm->file_path, entry->d_name);
			sprintf(f, "%s/%s", fm->file_path, entry->d_name);
			remove(f);
		}
	}
	closedir(dir);
		fm->upload_file = 0;
}

void fM_upload_offline_msg(struct filesManager* fm) {
	pthread_t pid;
	if (fm->upload_file)
		return ;
	fm->upload_file = 1;
	pthread_create(&pid, NULL, upload_offline_file, fm);
	pthread_detach(pid);
}

void fM_store_runtime_log(struct filesManager* fm, char* log) {
	time_t t;
	struct tm* tm_info;
	struct runTime* rt = fm->rt;
	char file[64];
	char msg[128];

	pthread_mutex_lock(&fm->lock_log_file);
	t = time(NULL);
	tm_info = localtime(&t);
	sprintf(file, "%s/log_%s", fm->file_path, rt->sn);
	sprintf(msg, "[%02d-%02d %02d:%02d] %s\n", 
			tm_info->tm_mon+1, tm_info->tm_mday, 
			tm_info->tm_hour, tm_info->tm_min, log);
	str_write_to_file(file, msg);
	pthread_mutex_unlock(&fm->lock_log_file);
}

void *update_img(void* arg) {
	struct filesManager* fm = (struct filesManager*)arg;
	ftp_download_file(fm->url, "/tmp/root_uImage_update");
	printf("start update ... \n");
	system("upgrade_mgr_n -S /tmp/root_uImage_update");
	system("reboot");
	fm->update_ing = 0;
}

void fM_download_img(struct filesManager* fm) {
	pthread_t pid;
	pthread_create(&pid, NULL, update_img, fm);
	pthread_detach(pid);
}



