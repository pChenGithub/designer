/*************************************************************************
	> File Name: listNode.h
	> Author: chen.peng
	> Mail: 404285202@qq.com 
	> Created Time: 2019年07月29日 星期一 11时35分49秒
 ************************************************************************/

#ifndef _LISTNODE_H_
#define _LISTNODE_H_
#include <stdio.h>

struct node {
	struct node* next;
	struct node* pre;
};

int insert_first(struct node* body);
int insert(struct node* head, struct node* body);
int remove_last(struct node* body);
int remove_node(struct node* body);

#endif
