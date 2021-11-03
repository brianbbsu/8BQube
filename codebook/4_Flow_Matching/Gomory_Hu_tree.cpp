struct Gomory_Hu_tree { // 0-base
  MaxFlow Dinic;
  int n;
  vector<pii> G[MAXN];
  void init(int _n) {
    n = _n;
    for (int i = 0; i < n; ++i) G[i].clear();
  }
  void solve(vector<int> &v) {
    if (v.size() <= 1) return;
    int s = rand() % SZ(v);
    swap(v.back(), v[s]), s = v.back();
    int t = v[rand() % (SZ(v) - 1)];
    vector<int> L, R;
    int x = (Dinic.reset(), Dinic.maxflow(s, t));
    G[s].pb(pii(t, x)), G[t].pb(pii(s, x));
    for (int i : v)
      if (~Dinic.dis[i]) L.pb(i);
      else
        R.pb(i);
    solve(L), solve(R);
  }
  void build() {
    vector<int> v(n);
    for (int i = 0; i < n; ++i) v[i] = i;
    solve(v);
  }
} ght; // test by BZOJ 4519
MaxFlow &Dinic = ght.Dinic;
