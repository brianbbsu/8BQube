template<typename Func, typename d = double>
struct Simpson {
  using pdd = pair<d, d>;
  Func f;
  pdd mix(pdd l, pdd r, optional<d> fm = {}) {
    d h = (r.X - l.X) / 2, v = fm.value_or(f(l.X + h));
    return {v, h / 3 * (l.Y + 4 * v + r.Y)};
  }
  d eval(pdd l, pdd r, d fm, d eps) {
    pdd m((l.X + r.X) / 2, fm);
    d s = mix(l, r, fm).second;
    auto [flm, sl] = mix(l, m);
    auto [fmr, sr] = mix(m, r);
    d delta = sl + sr - s;
    if (abs(delta) <= 15 * eps) return sl + sr + delta / 15;
    return eval(l, m, flm, eps / 2) +
      eval(m, r, fmr, eps / 2);
  }
  d eval(d l, d r, d eps) {
    return eval({l, f(l)}, {r, f(r)}, f((l + r) / 2), eps);
  }
  d eval2(d l, d r, d eps, int k = 997) {
    d h = (r - l) / k, s = 0;
    for (int i = 0; i < k; ++i, l += h)
      s += eval(l, l + h, eps / k);
    return s;
  }
};
template<typename Func>
Simpson<Func> make_simpson(Func f) { return {f}; }
