template<int MAXN>
struct FFT {
  using val_t = complex<double>;
  const double PI = acos(-1);
  val_t w[MAXN];
  FFT() {
    for (int i = 0; i < MAXN; ++i) {
      double arg = 2 * PI * i / MAXN;
      w[i] = val_t(cos(arg), sin(arg));
    }
  }
  void bitrev(val_t *a, int n) {
    int i = 0;
    for (int j = 1; j < n - 1; ++j) {
      for (int k = n >> 1; (i ^= k) < k; k >>= 1);
      if (j < i) swap(a[i], a[j]);
    }
  }
  void trans(val_t *a, int n, bool inv = false) {
    bitrev(a, n);
    for (int L = 2; L <= n; L <<= 1) {
      int dx = MAXN / L;
      for (int i = 0; i < n; i += L) {
        for (int j = i, x = 0; j < i + (L >> 1); ++j, x += dx) {
          val_t tmp = a[j + (L >> 1)] * w[x];
          a[j + (L >> 1)] = a[j] - tmp;
          a[j] += tmp;
        }
      }
    }
    if (inv) {
      reverse(a + 1, a + n);
      for (int i = 0; i < n; ++i) a[i] /= n;
    }
  }
};
