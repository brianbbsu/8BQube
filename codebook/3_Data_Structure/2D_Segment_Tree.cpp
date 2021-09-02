int num[501][501], N, M; // input here
struct seg_2D {
  struct node {
    int data;
    node *lc, *rc;
  } * root;
  node *merge(node *a, node *b, int l, int r) {
    node *p = new node;
    p->data = max(a->data, b->data);
    if (l == r) return p;
    int m = l + r >> 1;
    p->lc = merge(a->lc, b->lc, l, m);
    p->rc = merge(a->rc, b->rc, m + 1, r);
    return p;
  }
  node *build(int l, int r, int x) {
    node *p = new node;
    if (l == r) return p->data = num[x][l], p;
    int m = l + r >> 1;
    p->lc = build(l, m, x), p->rc = build(m + 1, r, x);
    p->data = max(p->lc->data, p->rc->data);
    return p;
  }
  int query(int L, int R, int l, int r, node *p) {
    if (L <= l && R >= r) return p->data;
    int m = l + r >> 1, re = 0;
    if (L <= m) re = query(L, R, l, m, p->lc);
    if (R > m)
      re = max(re, query(L, R, m + 1, r, p->rc));
    return re;
  }
};
struct seg_1D {
  struct node {
    seg_2D data;
    node *lc, *rc;
  } * root;
  node *s_build(int l, int r) {
    node *p = new node;
    if (l == r)
      return p->data.root = p->data.build(1, M, l), p;
    int m = l + r >> 1;
    p->lc = s_build(l, m), p->rc = s_build(m + 1, r);
    p->data.root = p->data.merge(
      p->lc->data.root, p->rc->data.root, 1, M);
    return p;
  }
  int s_query(int L, int R, int l, int r, node *p,
    int yl, int yr) {
    if (L <= l && R >= r)
      return p->data.query(yl, yr, 1, M, p->data.root);
    int m = l + r >> 1, re = 0;
    if (L <= m)
      re = s_query(L, R, l, m, p->lc, yl, yr);
    if (R > m)
      re = max(
        re, s_query(L, R, m + 1, r, p->rc, yl, yr));
    return re;
  }
  void init() { root = s_build(1, N); }
  int query(int xl, int xr, int yl, int yr) {
    return s_query(xl, xr, 1, N, root, yl, yr);
  }
};
