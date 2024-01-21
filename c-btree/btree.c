#include "btree.h"
#include <stdio.h>

int reb_count = 0;
int get_rebc() { return reb_count; }

// All arrays index start with 1, not 0.

int root = 0;
// tree size
int count = 0;
// alpha
double alpha = 0.75;
// magic number, set to 3 is the best.
int thresholding = 3;
// v[K] is node value for K
int v[MAXN] = {0};
// repeate times for K, 0 means deleted.
int w[MAXN] = {0};
// lt[K] is left tree for node K.
int lt[MAXN] = {0};
// rt[K] is right tree for node K.
int rt[MAXN] = {0};
// size = sum(node)
int s[MAXN] = {0};
// real size = sum(node if w[node] != 0)
int rs[MAXN] = {0};
// wedige size = sum(node*w[node])
int ws[MAXN] = {0};

static int max(int a, int b) { return a > b ? a : b; }

static bool should_rebuild(int r) {
  return s[r] > thresholding &&
         (alpha * s[r] < (double)max(s[lt[r]], s[rt[r]]) ||
          (double)rs[r] < alpha * s[r]);
}

// Generate node size for tree start at 'root'
static void gen_size(int r) {
  if (!r)
    return;

  gen_size(lt[r]);
  gen_size(rt[r]);
  // NOTE:
  // All arrays[0] = 0, because index 0 is not used.
  // size
  s[r] = s[lt[r]] + s[rt[r]] + 1;
  // wedige size
  ws[r] = ws[lt[r]] + ws[rt[r]] + w[r];
  // real size
  rs[r] = rs[lt[r]] + rs[rt[r]] + (w[r] > 0 ? 1 : 0);
}

// Generate a flat tree array.
static void flat(int r, int *flat_tree, int *tree_size) {
  if (!r)
    return;
  flat(lt[r], flat_tree, tree_size);
  // ignore deleted node
  if (w[r]) {
    flat_tree[*tree_size] = r;
    *tree_size += 1;
  } else {
    rs[r] = s[r] = ws[r] = 0;
  }
  flat(rt[r], flat_tree, tree_size);
}

// Generate tree from flat tree array.
// return root index
static int generate_tree(int *flat_tree, int l, int r) {
  if (l >= r || !flat_tree)
    return 0;

  int mid = (l + r) / 2;
  int k = flat_tree[mid];
  lt[k] = generate_tree(flat_tree, l, mid);
  rt[k] = generate_tree(flat_tree, mid + 1, r);
  return k;
}

// Rebuild tree at 'r'.
static int rebuild(int *r) {
  reb_count++;
  // flat tree
  int ft[MAXN] = {0};
  // (flat) tree size
  int ts = 0;
  flat(*r, ft, &ts);
  *r = generate_tree(ft, 0, ts);
  gen_size(*r);
  return *r;
}

int search_node(int r, int val) {
  if (!r)
    return 0;
  int child = 0;
  if (val < v[r])
    child = lt[r];
  else if (val > v[r])
    child = rt[r];
  else
    return w[r] ? r : 0;
  return search_node(child, val);
}

void insert_node(int *r, int val) {
  if (!r)
    return;
  if (!*r) {
    // insert new node
    int k = ++count;
    if (!root)
      root = k;
    w[k] = s[k] = rs[k] = ws[k] = 1;
    v[k] = val;
    *r = k;
  } else {
    if (val == v[*r])
      w[*r]++;
    else if (val < v[*r])
      insert_node(&lt[*r], val);
    else
      insert_node(&rt[*r], val);
  }
  if (should_rebuild(*r))
    rebuild(r);
  else
    gen_size(*r);
}

void delete_node(int *r, int val) {
  if (!r)
    return;
  if (val == v[*r]) {
    if (w[*r])
      w[*r]--;
  } else {
    if (val < v[*r])
      delete_node(&lt[*r], val);
    else
      delete_node(&rt[*r], val);
  }
  if (should_rebuild(*r))
    rebuild(r);
  else
    gen_size(*r);
}

void show_tree(int r) {
  if (!r)
    return;
  printf("r: %d, lt: %d, rt: %d, v: %d, s: %d, rs: %d, ws: %d, w: %d\n", r,
         lt[r], rt[r], v[r], s[r], rs[r], ws[r], w[r]);
  show_tree(lt[r]);
  show_tree(rt[r]);
}
