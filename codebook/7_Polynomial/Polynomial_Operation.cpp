#define fi(n) for (int i = 0; i < (int)(n); ++i)
int n2k(int n) {
  int sz = 1; while (sz < n) sz <<= 1;
  return sz;
}
template<int MAXN, LL P, LL RT> // MAXN = 2^k
struct Poly : public vector<LL> { // coefficients in [0, P)
  static NTT<MAXN, P, RT> ntt;
  static const LL INV2;
  int n() const { return (int)size(); }
  Poly(int _n = 1) : vector<LL>(_n) { }
  Poly(const LL *arr, int _n) : vector<LL>(_n) {
    copy_n(arr, _n, data());
  }
  Poly(const Poly &p, int _n) : vector<LL>(_n) {
    copy_n(p.data(), min(p.n(), _n), data());
  }
  Poly& operator=(const Poly &rhs) {
    clear(), insert(begin(), rhs.begin(), rhs.end());
    return *this;
  }
  Poly Mul(const Poly &rhs) const {
    int _n = n2k(n() + rhs.n() - 1);
    Poly X(*this, _n), Y(rhs, _n);
    ntt(X.data(), _n), ntt(Y.data(), _n);
    fi(_n) X[i] = X[i] * Y[i] % P;
    ntt(X.data(), _n, true);
    return X.resize(n() + rhs.n() - 1), X;
  }
  Poly Inv() const { // at(0) != 0
    if (n() == 1) {
      Poly ret(1);
      return ret[0] = ntt.minv(at(0)), ret;
    }
    int _n = n2k(n() * 2);
    Poly Xi = Poly(*this, (n() + 1) / 2).Inv();
    Poly Y(*this, _n); Xi.resize(_n);
    ntt(Xi.data(), _n), ntt(Y.data(), _n);
    fi(_n) {
      Xi[i] *= (2 - Xi[i] * Y[i]) % P;
      if ((Xi[i] %= P) < 0) Xi[i] += P;
    }
    ntt(Xi.data(), _n, true);
    return Xi.resize(n()), Xi;
  }
  Poly Sqrt() const { //at(0) != 0 && sqrt(at(0)) exists
    if (n() == 1) {
      Poly ret(1);
      return ret[0] = _msqrt(at(0)), ret;
    }
    int _n = n2k(n() * 2);
    Poly X = Poly(*this, (n() + 1) / 2).Sqrt();
    Poly Xi = Poly(X, n()).Inv();
    Poly Y(*this, _n); Xi.resize(_n); X.resize(_n);
    ntt(X.data(), _n), ntt(Xi.data(), _n), ntt(Y.data(), _n);
    fi(_n) {
        if ((X[i] += Y[i] * Xi[i] % P) >= P) X[i] -= P;
        X[i] = X[i] * INV2 % P;
    }
    ntt(X.data(), _n, true);
    return X.resize(n()), X;
  }
  Poly& irev() { reverse(data(), data() + n()); return *this;}
  pair<Poly, Poly> DivMod(const Poly &rhs) const { // (rhs.)back() != 0
    if (n() < rhs.n()) return {Poly(1), *this};
    int _n = n() - rhs.n() + 1;
    Poly X(rhs, rhs.n()); X.irev(); X.resize(_n);
    Poly Y(*this, n()); Y.irev(); Y.resize(_n);
    Poly Q = Y.Mul(X.Inv());
    Q.resize(_n); Q.irev();
    Poly XX = rhs.Mul(Q); Y.resize(n());
    assert(XX.n() == Y.n());
    fi(n()) if ((Y[i] = (*this)[i] - XX[i]) < 0) Y[i] += P;
    return {Q, (Y.resize(max(1, rhs.n() - 1)), Y)};
  }
};
template<int MAXN, LL P, LL RT> NTT<MAXN, P, RT> Poly<MAXN, P, RT>::ntt;
template<int MAXN, LL P, LL RT> const LL Poly<MAXN, P, RT>::INV2 = ntt.minv(2);
#undef fi
template<int MAXN> using Poly_t = Poly<MAXN, 998244353, 3>;