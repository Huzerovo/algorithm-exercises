#ifndef __BTREE_H
#define __BTREE_H

#include <stdbool.h>

#define MAXN 1024

int get_rebc();
void show_tree(int r);
int search_node(int r, int val);

void insert_node(int *r, int val);

void delete_node(int *r, int val);

#endif
