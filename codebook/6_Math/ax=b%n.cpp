vector<ll> mod_leq(ll a, ll b, ll n) {
  vector<ll> rt;
  ll g = gcd(a, n);
  pll p = exgcd(a, n);
  if (!(b % g)) {
    p.X = p.X * (b / g) % n;
    for (int i = 0; i < g; ++i)
      rt.pb(p.X), p.X = (p.X + n / g) % n;
  }
  return rt;
}
