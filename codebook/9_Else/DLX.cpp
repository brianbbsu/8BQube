template<bool Exact>
struct DLX {
  int lt[NN], rg[NN], up[NN], dn[NN], cl[NN], rw[NN], bt[NN], s[NN], head, sz, ans;
  int columns;
  bool vis[NN];
  void remove(int c) {
    if (Exact) lt[rg[c]] = lt[c], rg[lt[c]] = rg[c];
    for (int i = dn[c]; i != c; i = dn[i]) {
      if (Exact) {
        for (int j = rg[i]; j != i; j = rg[j])
          up[dn[j]] = up[j], dn[up[j]] = dn[j], --s[cl[j]];
      } else {
        lt[rg[i]] = lt[i], rg[lt[i]] = rg[i];
      }
    }
  }
  void restore(int c) {
    for (int i = up[c]; i != c; i = up[i]) {
      if (Exact) {
        for (int j = lt[i]; j != i; j = lt[j])
          ++s[cl[j]], up[dn[j]] = j, dn[up[j]] = j;
      } else {
        lt[rg[i]] = rg[lt[i]] = i;
      }
    }
    if (Exact) lt[rg[c]] = c, rg[lt[c]] = c;
  }
  void init(int c) {
    columns = c;
    for (int i = 0; i < c; ++i) {
      up[i] = dn[i] = bt[i] = i;
      lt[i] = i == 0 ? c : i - 1;
      rg[i] = i == c - 1 ? c : i + 1;
      s[i] = 0;
    }
    rg[c] = 0, lt[c] = c - 1;
    up[c] = dn[c] = -1;
    head = c, sz = c + 1;
  }
  void insert(int r, const vector<int> &col) {
    if (col.empty()) return;
    int f = sz;
    for (int i = 0; i < (int)col.size(); ++i) {
      int c = col[i], v = sz++;
      dn[bt[c]] = v;
      up[v] = bt[c], bt[c] = v;
      rg[v] = (i + 1 == (int)col.size() ? f : v + 1);
      rw[v] = r, cl[v] = c;
      ++s[c];
      if (i > 0) lt[v] = v - 1;
    }
    lt[f] = sz - 1;
  }
  int h() {
    int ret = 0;
    memset(vis, 0, sizeof(bool) * sz);
    for (int x = rg[head]; x != head; x = rg[x]) {
      if (vis[x]) continue;
      vis[x] = true, ++ret;
      for (int i = dn[x]; i != x; i = dn[i]) {
        for (int j = rg[i]; j != i; j = rg[j])
          vis[cl[j]] = true;
      }
    }
    return ret;
  }
  void dfs(int dep) {
    if (dep + (Exact ? 0 : h()) >= ans) return;
    if (rg[head] == head) return ans = dep, void();
    if (dn[rg[head]] == rg[head]) return;
    int c = rg[head];
    int w = c;
    for (int x = c; x != head; x = rg[x]) if (s[x] < s[w]) w = x;
    if (Exact) {
      remove(w);
      for (int i = dn[w]; i != w; i = dn[i]) {
        for (int j = rg[i]; j != i; j = rg[j]) remove(cl[j]);
        dfs(dep + 1);
        for (int j = lt[i]; j != i; j = lt[j]) restore(cl[j]);
      }
      restore(w);
    } else {
      for (int i = dn[w]; i != w; i = dn[i]) {
        remove(i);
        for (int j = rg[i]; j != i; j = rg[j]) remove(j);
        dfs(dep + 1);
        for (int j = lt[i]; j != i; j = lt[j]) restore(j);
        restore(i);
      }
    }
  }
  int solve() {
    for (int i = 0; i < columns; ++i)
      dn[bt[i]] = i, up[i] = bt[i];
    ans = 1e9, dfs(0);
    return ans;
  }
};
