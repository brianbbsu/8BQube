vector<pair<int, int>> rep[kN]; // 0-base [l, r]
void main_lorentz(const string &s, int sft = 0) {
  const int n = s.size();
  if (n == 1) return;
  const int nu = n / 2, nv = n - nu;
  const string u = s.substr(0, nu), v = s.substr(nu),
        ru(u.rbegin(), u.rend()), rv(v.rbegin(), v.rend());
  main_lorentz(u, sft), main_lorentz(v, sft + nu);
  const auto z1 = Zalgo(ru), z2 = Zalgo(v + '#' + u),
             z3 = Zalgo(ru + '#' + rv), z4 = Zalgo(v);
  auto get_z = [](const vector<int> &z, int i) {
    return (0 <= i and i < (int)z.size()) ? z[i] : 0; };
  auto add_rep = [&](bool left, int c, int l, int k1, int k2) {
    const int L = max(1, l - k2), R = min(l - left, k1);
    if (L > R) return;
    if (left) rep[l].emplace_back(sft + c - R, sft + c - L);
    else rep[l].emplace_back(sft + c - R - l + 1, sft + c - L - l + 1);
  };
  for (int cntr = 0; cntr < n; cntr++) {
    int l, k1, k2;
    if (cntr < nu) {
      l = nu - cntr;
      k1 = get_z(z1, nu - cntr);
      k2 = get_z(z2, nv + 1 + cntr);
    } else {
      l = cntr - nu + 1;
      k1 = get_z(z3, nu + 1 + nv - 1 - (cntr - nu));
      k2 = get_z(z4, (cntr - nu) + 1);
    }
    if (k1 + k2 >= l)
      add_rep(cntr < nu, cntr, l, k1, k2);
  }
}
