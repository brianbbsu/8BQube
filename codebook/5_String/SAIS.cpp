class SAIS {
public:
  int *SA, *H;
  // zero based, string content MUST > 0
  // result height H[i] is LCP(SA[i - 1], SA[i])
  // string, length, |sigma|
  void build(int *s, int n, int m = 128) {
    copy_n(s, n, _s);
    _h[0] = _s[n++] = 0;
    sais(_s, _sa, _p, _q, _t, _c, n, m);
    mkhei(n);
    SA = _sa + 1;
    H = _h + 1;
  }

private:
  bool _t[N * 2];
  int _s[N * 2], _c[N * 2], x[N], _p[N], _q[N * 2],
    r[N], _sa[N * 2], _h[N];
  void mkhei(int n) {
    for (int i = 0; i < n; i++) r[_sa[i]] = i;
    for (int i = 0; i < n; i++)
      if (r[i]) {
        int ans = i > 0 ? max(_h[r[i - 1]] - 1, 0) : 0;
        while (_s[i + ans] == _s[_sa[r[i] - 1] + ans])
          ans++;
        _h[r[i]] = ans;
      }
  }
  void sais(int *s, int *sa, int *p, int *q, bool *t,
    int *c, int n, int z) {
    bool uniq = t[n - 1] = 1, neq;
    int nn = 0, nmxz = -1, *nsa = sa + n, *ns = s + n,
        lst = -1;

#define MAGIC(XD)                                     \
  fill_n(sa, n, 0);                                   \
  copy_n(c, z, x);                                    \
  XD;                                                 \
  copy_n(c, z - 1, x + 1);                            \
  for (int i = 0; i < n; i++)                         \
    if (sa[i] && !t[sa[i] - 1])                       \
      sa[x[s[sa[i] - 1]]++] = sa[i] - 1;              \
  copy_n(c, z, x);                                    \
  for (int i = n - 1; i >= 0; i--)                    \
    if (sa[i] && t[sa[i] - 1])                        \
      sa[--x[s[sa[i] - 1]]] = sa[i] - 1;

    fill_n(c, z, 0);
    for (int i = 0; i < n; i++) uniq &= ++c[s[i]] < 2;
    partial_sum(c, c + z, c);
    if (uniq) {
      for (int i = 0; i < n; i++) sa[--c[s[i]]] = i;
      return;
    }
    for (int i = n - 2; i >= 0; i--)
      t[i] = (s[i] == s[i + 1] ? t[i + 1]
                               : s[i] < s[i + 1]);
    MAGIC(for (int i = 1; i <= n - 1;
               i++) if (t[i] && !t[i - 1])
            sa[--x[s[i]]] = p[q[i] = nn++] = i);
    for (int i = 0; i < n; i++)
      if (sa[i] && t[sa[i]] && !t[sa[i] - 1]) {
        neq = (lst < 0) ||
          !equal(s + lst,
            s + lst + p[q[sa[i]] + 1] - sa[i],
            s + sa[i]);
        ns[q[lst = sa[i]]] = nmxz += neq;
      }
    sais(ns, nsa, p + nn, q + n, t + n, c + z, nn,
      nmxz + 1);
    MAGIC(for (int i = nn - 1; i >= 0; i--)
            sa[--x[s[p[nsa[i]]]]] = p[nsa[i]]);
  }
} sa;
