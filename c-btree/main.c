#include "btree.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <unistd.h>

int main() {
  int root = 0;
  int count = 0;
  int seed = time(NULL);
  for (int i = 0; i < MAXN; i++) {
    seed = seed * (count + (count + 1) * 7);
    srand(seed);
    count++;
    insert_node(&root, floor(rand() * 10000));
    usleep(100);
  }
  printf("insert %d, rebuild %d, pro: %g%%\n", count, get_rebc(),
         ((double)get_rebc() / (double)count) * 100);
  // show_tree(root);
  return 0;
}
