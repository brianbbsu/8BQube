bool PointInConvex(const vector<pll> &C, pll p, bool strict = true) {
  int a = 1, b = SZ(C) - 1, r = !strict;
  if (SZ(C) == 0) return false;
  if (SZ(C) < 3) return r && btw(C[0], C.back(), p);
  if (ori(l[0], l[a], l[b]) > 0) swap(a, b);
  if (ori(l[0], l[a], p) >= r || ori(l[0], l[b], p) <= -r)
    return false;
  while (abs(a - b) > 1) {
    int c = (a + b) / 2;
    (ori(l[0], l[c], p) > 0 ? b : a) = c;
  }
  return ori(l[a], l[b], p) < r;
}
