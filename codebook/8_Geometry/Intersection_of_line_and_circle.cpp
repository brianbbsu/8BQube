vector<pdd> circleLine(pdd c, double r, pdd a, pdd b) {
  pdd p = a + (b - a) * dot(c - a, b - a) / abs2(b - a);
  double s = cross(b - a, c - a), h2 = r * r - s * s / abs2(b - a);
  if (h2 < 0) return {};
  if (h2 == 0) return {p};
  pdd h = (b - a) / abs(b - a) * sqrt(h2);
  return {p - h, p + h};
}
