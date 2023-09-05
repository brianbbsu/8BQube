/* The point should be strictly out of hull
   return arbitrary point on the tangent line */
pii get_tangent(vector<pll> &C, pll p) {
  int N = SZ(C);
  auto gao = [&](int s) {
    auto lt = [&](int x, int y) 
    { return ori(p, C[y % N], C[x % N]) == s; };
    int l = 0, r = N; bool up = lt(0, 1);
    while (r - l > 1) {
      int m = (l + r) / 2;
      if (lt(m, 0) ? up : !lt(m, m + 1)) r = m;
      else l = m;
    }
    return (lt(l, r) ? r : l) % N;
  };
  return pii(gao(1), gao(-1));
} // return (a, b), ori(p, C[a], C[b]) > 0
