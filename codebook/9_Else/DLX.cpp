#define TRAV(i, link, start) for (int i = link[start]; i != start; i = link[i])
template<bool E> // E: Exact, NN: num of 1s, RR: num of rows
struct DLX {
  int lt[NN], rg[NN], up[NN], dn[NN], rw[NN], cl[NN], bt[NN], s[NN], head, sz, ans;
  int rows, columns;
  bool vis[NN];
  bitset<RR> sol, cur; // not sure
  void remove(int c) {
    if (E) lt[rg[c]] = lt[c], rg[lt[c]] = rg[c];
    TRAV(i, dn, c) {
      if (E) {
        TRAV(j, rg, i)
          up[dn[j]] = up[j], dn[up[j]] = dn[j], --s[cl[j]];
      } else {
        lt[rg[i]] = lt[i], rg[lt[i]] = rg[i];
      }
    }
  }
  void restore(int c) {
    TRAV(i, up, c) {
      if (E) {
        TRAV(j, lt, i)
          ++s[cl[j]], up[dn[j]] = j, dn[up[j]] = j;
      } else {
        lt[rg[i]] = rg[lt[i]] = i;
      }
    }
    if (E) lt[rg[c]] = c, rg[lt[c]] = c;
  }
  void init(int c) {
    rows = 0, columns = c;
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
  void insert(const vector<int> &col) {
    if (col.empty()) return;
    int f = sz;
    for (int i = 0; i < (int)col.size(); ++i) {
      int c = col[i], v = sz++;
      dn[bt[c]] = v;
      up[v] = bt[c], bt[c] = v;
      rg[v] = (i + 1 == (int)col.size() ? f : v + 1);
      rw[v] = rows, cl[v] = c;
      ++s[c];
      if (i > 0) lt[v] = v - 1;
    }
    ++rows, lt[f] = sz - 1;
  }
  int h() {
    int ret = 0;
    fill_n(vis, sz, false);
    TRAV(x, rg, head) {
      if (vis[x]) continue;
      vis[x] = true, ++ret;
      TRAV(i, dn, x) TRAV(j, rg, i) vis[cl[j]] = true;
    }
    return ret;
  }
  void dfs(int dep) {
    if (dep + (E ? 0 : h()) >= ans) return;
    if (rg[head] == head) return sol = cur, ans = dep, void();
    if (dn[rg[head]] == rg[head]) return;
    int w = rg[head];
    TRAV(x, rg, head) if (s[x] < s[w]) w = x;
    if (E) remove(w);
    TRAV(i, dn, w) {
      if (!E) remove(i);
      TRAV(j, rg, i) remove(E ? cl[j] : j);
      cur.set(rw[i]), dfs(dep + 1), cur.reset(rw[i]);
      TRAV(j, lt, i) restore(E ? cl[j] : j);
      if (!E) restore(i);
    }
    if (E) restore(w);
  }
  int solve() {
    for (int i = 0; i < columns; ++i)
      dn[bt[i]] = i, up[i] = bt[i];
    ans = 1e9, sol.reset(), dfs(0);
    return ans;
  }
};
