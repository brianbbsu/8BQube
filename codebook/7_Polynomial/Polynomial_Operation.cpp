#define fi(s, n) for (int i = (int)(s); i < (int)(n); ++i)
#define Fi(s, n) for (int i = (int)(n); i > (int)(s); --i)
int n2k(int n) {
  int sz = 1; while (sz < n) sz <<= 1;
  return sz;
}
template<int MAXN, LL P, LL RT> // MAXN = 2^k
struct Poly { // coefficients in [0, P)
  static NTT<MAXN, P, RT> ntt;
  static const LL INV2;

  vector<LL> coef;
  int n() const { return (int)coef.size(); } // n() >= 1
  LL *data() { return coef.data(); }
  const LL *data() const { return coef.data(); }
  LL &operator[](size_t i) { return data()[i]; }
  const LL &operator[](size_t i) const { return data()[i]; }
  Poly(initializer_list<LL> a) : coef(a) { }
  explicit Poly(int _n = 1) : coef(_n) { }
  Poly(const LL *arr, int _n) : coef(arr, arr + _n) {}
  Poly(const Poly &p, int _n) : coef(_n) {
    copy_n(p.data(), min(p.n(), _n), data());
  }
  Poly& irev() { return reverse(data(), data() + n()), *this; }
  Poly& iresz(int _n) { return coef.resize(_n), *this; }

  Poly Mul(const Poly &rhs) const {
    const int _n = n2k(n() + rhs.n() - 1);
    Poly X(*this, _n), Y(rhs, _n);
    ntt(X.data(), _n), ntt(Y.data(), _n);
    fi(0, _n) X[i] = X[i] * Y[i] % P;
    ntt(X.data(), _n, true);
    return X.iresz(n() + rhs.n() - 1);
  }
  Poly Inv() const { // at(0) != 0
    if (n() == 1) return {ntt.minv(data()[0])};
    const int _n = n2k(n() * 2);
    Poly Xi = Poly(*this, (n() + 1) / 2).Inv().iresz(_n);
    Poly Y(*this, _n);
    ntt(Xi.data(), _n), ntt(Y.data(), _n);
    fi(0, _n) {
      Xi[i] *= (2 - Xi[i] * Y[i]) % P;
      if ((Xi[i] %= P) < 0) Xi[i] += P;
    }
    ntt(Xi.data(), _n, true);
    return Xi.iresz(n());
  }
  Poly Sqrt() const { //data()[0] != 0 && sqrt(at(0)) exists
    if (n() == 1) return {QuadraticResidue(data()[0], P)};
    const int _n = n2k(n() * 2);
    Poly X = Poly(*this, (n() + 1) / 2).Sqrt().iresz(_n);
    Poly Xi = Poly(X, n()).Inv().iresz(_n), Y(*this, _n);
    ntt(X.data(), _n), ntt(Xi.data(), _n), ntt(Y.data(), _n);
    fi(0, _n) {
        if ((X[i] += Y[i] * Xi[i] % P) >= P) X[i] -= P;
        X[i] = X[i] * INV2 % P;
    }
    ntt(X.data(), _n, true);
    return X.iresz(n());
  }
  pair<Poly, Poly> DivMod(const Poly &rhs) const { // (rhs.)back() != 0
    if (n() < rhs.n()) return {{0}, *this};
    const int _n = n() - rhs.n() + 1;
    Poly X(rhs, rhs.n()); X.irev().iresz(_n);
    Poly Y(*this, n()); Y.irev().iresz(_n);
    Poly Q = Y.Mul(X.Inv()).iresz(_n).irev();
    Poly XX = rhs.Mul(Q); Y.iresz(n());
    fi(0, n()) if ((Y[i] = (*this)[i] - XX[i]) < 0) Y[i] += P;
    return {Q, Y.iresz(max(1, rhs.n() - 1))};
  }
  Poly Derivative() const {
    Poly ret(n() - 1);
    fi(0, ret.n()) ret[i] = (i + 1) * (*this)[i + 1] % P;
    if (!ret.n()) ret.coef.push_back(0);
    return ret;
  }
  Poly Integral() const {
    Poly ret(n() + 1);
    fi(0, n()) ret[i + 1] = ntt.minv(i + 1) * (*this)[i] % P;
    return ret;
  }
  vector<LL> Eval(const vector<LL> &x) const {
    const int _n = (int)x.size();
    if (!_n) return {};
    vector<Poly> node(_n * 2);
    fi(0, _n) node[_n + i] = {(x[i] % P ? P - x[i] % P : 0), 1};
    Fi(0, _n - 1) node[i] = node[i * 2].Mul(node[i * 2 + 1]);
    node[0] = *this;
    fi(1, _n * 2) node[i] = node[i / 2].DivMod(node[i]).second;
    vector<LL> y(_n);
    fi(0, _n) y[i] = node[_n + i][0];
    return y;
  }
  Poly MulT(int nn, const Poly &rhs) const { // n() + nn - 1 >= rhs.n()
    Poly Y = Poly(*this, n()).irev().Mul(rhs).iresz(n() + nn - 1);
    return Poly(Y.data() + n() - 1, nn);
  }
  vector<LL> Eval2(const vector<LL> &x) const {
    const int _n = (int)x.size();
    if (!_n) return {};
    vector<Poly> up(_n * 2), down(_n * 2);
    fi(0, _n) up[_n + i] = {1, (x[i] % P ? P - x[i] % P : 0)};
    Fi(0, _n - 1) up[i] = up[i * 2].Mul(up[i * 2 + 1]);
    down[1] = up[1].iresz(n()).Inv().MulT(_n, *this);
    fi(2, _n * 2) down[i] = up[i ^ 1].MulT(up[i].n() - 1, down[i / 2]);
    vector<LL> y(_n);
    fi(0, _n) y[i] = down[_n + i][0];
    return y;
  }
  Poly Interpolate(const vector<LL> &x, const vector<LL> &y) const {
    const int _n = (int)x.size();
  }
};
#undef fi
#undef Fi
template<int MAXN, LL P, LL RT> NTT<MAXN, P, RT> Poly<MAXN, P, RT>::ntt;
template<int MAXN, LL P, LL RT> const LL Poly<MAXN, P, RT>::INV2 = ntt.minv(2);
using Poly_t = Poly<131072 * 2, 998244353, 3>;
