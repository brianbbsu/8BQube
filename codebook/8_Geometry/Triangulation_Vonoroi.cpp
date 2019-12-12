int gid(P &p) {
    auto it = ptoid.find(p);
    if (it == ptoid.end()) return -1;
    return it->second;
}
L make_line(P p, L l) {
    P d = l.pb - l.pa; d = d.spin(pi / 2);
    P m = (l.pa + l.pb) / 2;
    l = L(m, m + d);
    if (((l.pb - l.pa) ^ (p - l.pa)) < 0) l = L(m + d, m);
    return l;
}
double calc_ans(int i) {
    vector<P> ps = HPI(ls[i]);
    double rt = 0;
    for (int i = 0; i < (int)ps.size(); ++i) {
        rt += (ps[i] ^ ps[(i + 1) % ps.size()]);
    }
    return abs(rt) / 2;
}
void solve() {
    for (int i = 0; i < n; ++i) ops[i] = ps[i], ptoid[ops[i]] = i;
    random_shuffle(ps, ps + n);
    build(n, ps);
    for (auto *t : triang) {
        int z[3] = {gid(t->p[0]), gid(t->p[1]), gid(t->p[2])};
        for (int i = 0; i < 3; ++i) for (int j = 0; j < 3; ++j) if (i != j && z[i] != -1 && z[j] != -1) {
            L l(t->p[i], t->p[j]);
            ls[z[i]].push_back(make_line(t->p[i], l));
        }
    }
    vector<P> tb = convex(vector<P>(ps, ps + n));
    for (auto &p : tb) isinf[gid(p)] = true;
    for (int i = 0; i < n; ++i) {
        if (isinf[i]) cout << -1 << '\n';
        else cout << fixed << setprecision(12) << calc_ans(i) << '\n';
    }
}
