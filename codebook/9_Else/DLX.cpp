namespace dlx {
int lt[maxn], rg[maxn], up[maxn], dn[maxn], cl[maxn], rw[maxn], bt[maxn], s[maxn], head, sz, ans;
void init(int c) {
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
void remove(int c) {
    lt[rg[c]] = lt[c], rg[lt[c]] = rg[c];
    for (int i = dn[c]; i != c; i = dn[i]) {
        for (int j = rg[i]; j != i; j = rg[j])
            up[dn[j]] = up[j], dn[up[j]] = dn[j], --s[cl[j]];
    }
}
void restore(int c) {
    for (int i = up[c]; i != c; i = up[i]) {
        for (int j = lt[i]; j != i; j = lt[j])
            ++s[cl[j]], up[dn[j]] = j, dn[up[j]] = j;
    }
    lt[rg[c]] = c, rg[lt[c]] = c;
}
// Call dlx::make after inserting all rows.
void make(int c) {
    for (int i = 0; i < c; ++i)
        dn[bt[i]] = i, up[i] = bt[i];
}
void dfs(int dep) {
    if (dep >= ans) return;
    if (rg[head] == head) return ans = dep, void();
    if (dn[rg[head]] == rg[head]) return;
    int c = rg[head];
    int w = c;
    for (int x = c; x != head; x = rg[x]) if (s[x] < s[w]) w = x;
    remove(w);
    for (int i = dn[w]; i != w; i = dn[i]) {
        for (int j = rg[i]; j != i; j = rg[j]) remove(cl[j]);
        dfs(dep + 1);
        for (int j = lt[i]; j != i; j = lt[j]) restore(cl[j]);
    }
    restore(w);
}
int solve() {
  ans = 1e9, dfs(0);
  return ans;
}}