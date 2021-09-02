struct Binary_Index_Tree {
  int bit[MAXN + 1], lazy[MAXN + 1], n;
  int lb(int x) { return x & -x; }
  void init(int _n, int *data) {
    n = _n;
    for (int i = 1, t; i <= n; ++i) {
      bit[i] = data[i], lazy[i] = 0, t = i - lb(i);
      for (int j = i - 1; j > t; j -= lb(j))
        bit[i] += bit[j];
    }
  }
  void suf_modify(int x, int v) {
    for (int t = x; t; t -= lb(t)) lazy[t] += v;
    for (int t = x + lb(x); t && t <= n; t += lb(t))
      bit[t] += v * (x - t + lb(t));
  }
  void modify(int x, int v) {
    for (; x; x -= lb(x)) bit[x] += v;
  }
  int query(int x) {
    int re = 0;
    for (int t = x; t; t -= lb(t))
      re += lazy[t] * lb(t) + bit[t];
    for (int t = x + lb(x); t && t <= n; t += lb(t))
      re += lazy[t] * (x - t + lb(t));
    return re;
  }
};
