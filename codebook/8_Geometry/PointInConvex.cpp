bool PointInConvex(const vector<pll> &C, pdd p) {
  if (SZ(C) == 0) return false;
  if (SZ(C) == 1) return abs(C[0] - p) < eps;
  if (SZ(C) == 2) return btw(C[0], C[1], p);
  for (int i = 0; i < SZ(C); ++i) {
    const int j = i + 1 == SZ(C) ? 0 : i + 1;
    if (cross(C[j] - C[i], p - C[i]) < -eps)
      return false;
  }
  return true;
}
