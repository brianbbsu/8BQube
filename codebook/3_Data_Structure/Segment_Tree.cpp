struct Segment_Tree {
  struct node {
    int data, lazy;
    node *l, *r;
    node() : data(0), lazy(0), l(0), r(0) {}
    void up() {
      if (l) data = max(l->data, r->data);
    }
    void down() {
      if (l) {
        l->data += lazy, l->lazy += lazy;
        r->data += lazy, r->lazy += lazy;
      }
      lazy = 0;
    }
  } * root;
  int l, r;
  node *build(int l, int r, int *data) {
    node *p = new node();
    if (l == r) return p->data = data[l], p;
    int m = (l + r) / 2;
    p->l = build(l, m, data),
    p->r = build(m + 1, r, data);
    return p->up(), p;
  }
  void s_modify(
    int L, int R, int l, int r, node *p, int x) {
    if (r < L || l > R) return;
    p->down();
    if (L <= l && R >= r)
      return p->data += x, p->lazy += x, void();
    int m = (l + r) / 2;
    s_modify(L, R, l, m, p->l, x);
    s_modify(L, R, m + 1, r, p->r, x);
    p->up();
  }
  int s_query(int L, int R, int l, int r, node *p) {
    p->down();
    if (L <= l && R >= r) return p->data;
    int m = (l + r) / 2;
    if (R <= m) return s_query(L, R, l, m, p->l);
    if (L > m) return s_query(L, R, m + 1, r, p->r);
    return max(s_query(L, R, l, m, p->l),
      s_query(L, R, m + 1, r, p->r));
  }
  void init(int L, int R, int *data) {
    l = L, r = R;
    root = build(l, r, data);
  }
  void modify(int L, int R, int x) {
    s_modify(L, R, l, r, root, x);
  }
  int query(int L, int R) {
    return s_query(L, R, l, r, root);
  }
};
