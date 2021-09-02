struct Sparse_table {
  int st[__lg(MAXN) + 1][MAXN], n;
  void init(int _n, int *data) {
    n = _n;
    for (int i = 0; i < n; ++i) st[i][0] = data[i];
    for (int i = 1, t = 2; t < n; t <<= 1, i++)
      for (int j = 0; j + t <= n; j++)
        st[i][j] =
          max(st[i - 1][j], st[i - 1][j + t / 2]);
  }
  int query(int a, int b) {
    int t = __lg(b - a + 1);
    return max(st[t][a], st[t][b - (1 << t) + 1]);
  }
};
