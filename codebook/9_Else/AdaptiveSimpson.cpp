using F_t = function<double(double)>;
pdd simpson(const F_t &f, double l, double r,
  double fl, double fr, double fm = nan("")) {
  if (isnan(fm)) fm = f((l + r) / 2);
  return {fm, (r - l) / 6 * (fl + 4 * fm + fr)};
}
double simpson_ada(const F_t &f, double l, double r,
  double fl, double fm, double fr, double eps) {
  double m = (l + r) / 2,
         s = simpson(f, l, r, fl, fr, fm).second;
  auto [flm, sl] = simpson(f, l, m, fl, fm);
  auto [fmr, sr] = simpson(f, m, r, fm, fr);
  double delta = sl + sr - s;
  if (abs(delta) <= 15 * eps)
    return sl + sr + delta / 15;
  return simpson_ada(f, l, m, fl, flm, fm, eps / 2) +
    simpson_ada(f, m, r, fm, fmr, fr, eps / 2);
}
double simpson_ada(const F_t &f, double l, double r) {
  return simpson_ada(
    f, l, r, f(l), f((l + r) / 2), f(r), 1e-9 / 7122);
}
double simpson_ada2(const F_t &f, double l, double r) {
    double h = (r - l) / 7122, s = 0;
  for (int i = 0; i < 7122; ++i, l += h)
    s += simpson_ada(f, l, l + h);
  return s;
}
