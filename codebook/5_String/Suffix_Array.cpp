struct suffix_array {
  int box[MAXN], tp[MAXN], m;
  bool not_equ(int a, int b, int k, int n) {
    return ra[a] != ra[b] || a + k >= n ||
      b + k >= n || ra[a + k] != ra[b + k];
  }
  void radix(int *key, int *it, int *ot, int n) {
    fill_n(box, m, 0);
    for (int i = 0; i < n; ++i) ++box[key[i]];
    partial_sum(box, box + m, box);
    for (int i = n - 1; i >= 0; --i)
      ot[--box[key[it[i]]]] = it[i];
  }
  void make_sa(const string &s, int n) {
    int k = 1;
    for (int i = 0; i < n; ++i) ra[i] = s[i];
    do {
      iota(tp, tp + k, n - k), iota(sa + k, sa + n, 0);
      radix(ra + k, sa + k, tp + k, n - k);
      radix(ra, tp, sa, n);
      tp[sa[0]] = 0, m = 1;
      for (int i = 1; i < n; ++i) {
        m += not_equ(sa[i], sa[i - 1], k, n);
        tp[sa[i]] = m - 1;
      }
      copy_n(tp, n, ra);
      k *= 2;
    } while (k < n && m != n);
  }
  void make_he(const string &s, int n) {
    for (int j = 0, k = 0; j < n; ++j) {
      if (ra[j])
        for (; s[j + k] == s[sa[ra[j] - 1] + k]; ++k)
          ;
      he[ra[j]] = k, k = max(0, k - 1);
    }
  }
  int sa[MAXN], ra[MAXN], he[MAXN];
  void build(const string &s) {
    int n = SZ(s);
    fill_n(sa, n, 0), fill_n(ra, n, 0), fill_n(he, n, 0);
    fill_n(box, n, 0), fill_n(tp, n, 0), m = 256;
    make_sa(s, n), make_he(s, n);
  }
};
