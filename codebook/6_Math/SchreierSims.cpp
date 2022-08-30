namespace schreier {
int n;
vector<vector<vector<int>>> bkts, binv;
vector<vector<int>> lk;
vector<int> operator*(const vector<int> &a, const vector<int> &b) {
  vector<int> res(SZ(a));
  for (int i = 0; i < SZ(a); ++i) res[i] = b[a[i]];
  return res;
}
vector<int> inv(const vector<int> &a) {
  vector<int> res(SZ(a));
  for (int i = 0; i < SZ(a); ++i) res[a[i]] = i;
  return res;
}
int filter(const vector<int> &g, bool add = true) {
  n = SZ(bkts);
  vector<int> p = g;
  for (int i = 0; i < n; ++i) {
    assert(p[i] >= 0 && p[i] < SZ(lk[i]));
    if (lk[i][p[i]] == -1) {
      if (add) {
        bkts[i].pb(p);
        binv[i].pb(inv(p));
        lk[i][p[i]] = SZ(bkts[i]) - 1;
      }
      return i;
    }
    p = p * binv[i][lk[i][p[i]]];
  }
  return -1;
}
bool inside(const vector<int> &g) { return filter(g, false) == -1; }
void solve(const vector<vector<int>> &gen, int _n) {
  n = _n;
  bkts.clear(), bkts.resize(n);
  binv.clear(), binv.resize(n);
  lk.clear(), lk.resize(n);
  vector<int> iden(n);
  iota(iden.begin(), iden.end(), 0);
  for (int i = 0; i < n; ++i) {
    lk[i].resize(n, -1);
    bkts[i].pb(iden);
    binv[i].pb(iden);
    lk[i][i] = 0;
  }
  for (int i = 0; i < SZ(gen); ++i) filter(gen[i]);
  queue<pair<pii, pii>> upd;
  for (int i = 0; i < n; ++i)
    for (int j = i; j < n; ++j)
      for (int k = 0; k < SZ(bkts[i]); ++k)
        for (int l = 0; l < SZ(bkts[j]); ++l)
          upd.emplace(pii(i, k), pii(j, l));
  while (!upd.empty()) {
    auto a = upd.front().X;
    auto b = upd.front().Y;
    upd.pop();
    int res = filter(bkts[a.X][a.Y] * bkts[b.X][b.Y]);
    if (res == -1) continue;
    pii pr = pii(res, SZ(bkts[res]) - 1);
    for (int i = 0; i < n; ++i)
      for (int j = 0; j < SZ(bkts[i]); ++j) {
        if (i <= res) upd.emplace(pii(i, j), pr);
        if (res <= i) upd.emplace(pr, pii(i, j));
      }
  }
}
ll size() {
  ll res = 1;
  for (int i = 0; i < n; ++i) res = res * SZ(bkts[i]);
  return res;
}}
