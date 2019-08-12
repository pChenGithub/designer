/*************************************************************************
	> File Name: listNode.c
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年07月29日 星期一 11时41分18秒
 ************************************************************************/

#include "listNode.h"

int insert_first(struct node* body) {

	if (!body) {
	
		perror("body is null \n");
		return -1;
	}

	body->next = body;
	body->pre = body;
	return 0;
}

int insert(struct node* head, struct node* body) {

	if (!head || !body || head==body ) {
	
		perror("node head or body is null, or head==body  \n");
		return -1;
	}

	body->next = head->next;
	head->next->pre = body;
	head->next = body;
	body->pre = head;

	return 0;
}

int remove_last(struct node* body) {

	return 0;
}

int remove_node(struct node* body) {

	if (!body || body->next==body || body->pre==body) {
	
		perror("node body is null  \n");
		return -1;
	}

	body->pre->next = body->next;
	body->next->pre = body->pre;

	return 0;
}


