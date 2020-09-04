struct PiCount {
  vector<int> pr;
  int prc[MAXN];
  ll phic[MSZ][NSZ];
  void init() {
    bitset<MAXN> v;
    pr.push_back(0);
    for (int i = 2; i < MAXN; ++i) {
      if (!v[i]) pr.push_back(i);
      for (int j = 1; i * pr[j] < MAXN; ++j) {
        v[i * pr[j]] = true;
        if (i % pr[j] == 0) break;
      }
    }
    for (int i = 1; i < pr.size(); ++i) prc[pr[i]] = 1;
    for (int i = 1; i < MAXN; ++i) prc[i] += prc[i - 1];
    memset(phic, -1, sizeof(phic));
  }
  ll phi(ll m, ll n) {
    if (m < MSZ && n < NSZ && phic[m][n] != -1) return phic[m][n];
    if (n == 0) return m;
    if (pr[n] >= m) return 1;
    ll ret = phi(m, n - 1) - phi(m / pr[n], n - 1);
    if (m < MSZ && n < NSZ) phic[m][n] = ret;
    return ret;
  }
  ll p2(ll m, ll n) {
    ll ret = 0, lim = sqrt(m);
    while (pr[++n] <= lim) ret += pi(m / pr[n]) - pi(pr[n]) + 1;
    return ret;
  }
  ll pi(ll m) {
    if (m < MAXN) return prc[m];
    ll n = pi(cbrt(m));
    return phi(m, n) + n - 1 - p2(m, n);
  }
};
