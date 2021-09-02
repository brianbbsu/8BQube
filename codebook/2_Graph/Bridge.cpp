int low[N], dfn[N], Time; // 1-base
vector<pii> G[N], edge;
vector<bool> is_bridge;

void init(int n) {
  Time = 0;
  for (int i = 1; i <= n; ++i)
    G[i].clear(), low[i] = dfn[i] = 0;
}

void add_edge(int a, int b) {
  G[a].pb(pii(b, SZ(edge))), G[b].pb(pii(a, SZ(edge)));
  edge.pb(pii(a, b));
}

void dfs(int u, int f) {
  dfn[u] = low[u] = ++Time;
  for (auto i : G[u])
    if (!dfn[i.X])
      dfs(i.X, i.Y), low[u] = min(low[u], low[i.X]);
    else if (i.Y != f) low[u] = min(low[u], dfn[i.X]);
  if (low[u] == dfn[u] && f != -1) is_bridge[f] = 1;
}

void solve(int n) {
  is_bridge.resize(SZ(edge));
  for (int i = 1; i <= n; ++i)
    if (!dfn[i]) dfs(i, -1);
}
