struct Edge { int to, cap, rev, cost; };
vector<Edge> g[kN];
int dist[kN], pv[kN], ed[kN];
bool mark[kN];
int NegativeCycle(int n) {
  memset(mark, false, sizeof(mark));
  memset(dist, 0, sizeof(dist));
  int upd = -1;
  for (int i = 0; i <= n; ++i) {
    for (int j = 0; j < n; ++j) {
      int idx = 0;
      for (auto &e : g[j]) {
        if (e.cap > 0 && dist[e.to] > dist[j] + e.cost) {
          dist[e.to] = dist[j] + e.cost;
          pv[e.to] = j, ed[e.to] = idx;
          if (i == n) {
            upd = j;
            while (!mark[upd]) mark[upd] = true, upd = pv[upd];
            return upd;
          }
        }
        idx++;
      }
    }
  }
  return -1;
}
int Solve(int n) {
  int rt = -1, ans = 0;
  while ((rt = NegativeCycle(n)) >= 0) {
    memset(mark, false, sizeof(mark));
    vector<pair<int, int>> cyc;
    while (!mark[rt]) {
      cyc.emplace_back(pv[rt], ed[rt]);
      mark[rt] = true;
      rt = pv[rt];
    }
    reverse(cyc.begin(), cyc.end());
    int cap = kInf;
    for (auto &i : cyc) {
      auto &e = g[i.first][i.second];
      cap = min(cap, e.cap);
    }
    for (auto &i : cyc) {
      auto &e = g[i.first][i.second];
      e.cap -= cap;
      g[e.to][e.rev].cap += cap;
      ans += e.cost * cap;
    }
  }
  return ans;
}
