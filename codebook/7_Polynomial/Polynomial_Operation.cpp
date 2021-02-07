#define fi(s, n) for (int i = (int)(s); i < (int)(n); ++i)
#define Fi(s, n) for (int i = (int)(n); i > (int)(s); --i)
int n2k(int n) {
  int sz = 1; while (sz < n) sz <<= 1;
  return sz;
}
template<int MAXN, LL P, LL RT> // MAXN = 2^k
struct Poly : public vector<LL> { // coefficients in [0, P)
  static NTT<MAXN, P, RT> ntt;
  static const LL INV2;
  int n() const { return (int)size(); } // n() >= 1
  explicit Poly(int _n = 1) : vector<LL>(_n) { }
  Poly(initializer_list<LL> a) : vector<LL>(a) { }
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
    fi(0, _n) X[i] = X[i] * Y[i] % P;
    ntt(X.data(), _n, true);
    return X.resize(n() + rhs.n() - 1), X;
  }
  Poly Inv() const { // at(0) != 0
    if (n() == 1) return {ntt.minv(at(0))};
    int _n = n2k(n() * 2);
    Poly Xi = Poly(*this, (n() + 1) / 2).Inv();
    Poly Y(*this, _n); Xi.resize(_n);
    ntt(Xi.data(), _n), ntt(Y.data(), _n);
    fi(0, _n) {
      Xi[i] *= (2 - Xi[i] * Y[i]) % P;
      if ((Xi[i] %= P) < 0) Xi[i] += P;
    }
    ntt(Xi.data(), _n, true);
    return Xi.resize(n()), Xi;
  }
  Poly Sqrt() const { //at(0) != 0 && sqrt(at(0)) exists
    if (n() == 1) return {QuadraticResidue(at(0), P)};
    int _n = n2k(n() * 2);
    Poly X = Poly(*this, (n() + 1) / 2).Sqrt();
    Poly Xi = Poly(X, n()).Inv();
    Poly Y(*this, _n); Xi.resize(_n); X.resize(_n);
    ntt(X.data(), _n), ntt(Xi.data(), _n), ntt(Y.data(), _n);
    fi(0, _n) {
        if ((X[i] += Y[i] * Xi[i] % P) >= P) X[i] -= P;
        X[i] = X[i] * INV2 % P;
    }
    ntt(X.data(), _n, true);
    return X.resize(n()), X;
  }
  Poly& irev() { reverse(data(), data() + n()); return *this;}
  pair<Poly, Poly> DivMod(const Poly &rhs) const { // (rhs.)back() != 0
    if (n() < rhs.n()) return {{0}, *this};
    int _n = n() - rhs.n() + 1;
    Poly X(rhs, rhs.n()); X.irev(); X.resize(_n);
    Poly Y(*this, n()); Y.irev(); Y.resize(_n);
    Poly Q = Y.Mul(X.Inv());
    Q.resize(_n); Q.irev();
    Poly XX = rhs.Mul(Q); Y.resize(n());
    fi(0, n()) if ((Y[i] = (*this)[i] - XX[i]) < 0) Y[i] += P;
    return {Q, (Y.resize(max(1, rhs.n() - 1)), Y)};
  }
  Poly Derivative() const {
    Poly ret(n() - 1);
    fi(0, ret.n()) ret[i] = (i + 1) * (*this)[i + 1] % P;
    if (ret.empty()) ret.push_back(0);
    return ret;
  }
  Poly Integral() const {
    Poly ret(n() + 1);
    fi(0, n()) ret[i + 1] = ntt.minv(i + 1) * (*this)[i] % P;
    return ret;
  }
  vector<LL> Eval(const vector<LL> &x) const {
    const int _n = x.size();
    vector<Poly> node(_n * 2);
    fi(0, _n) node[_n + i] = {(x[i] % P ? P - x[i] % P : 0), 1};
    Fi(0, _n - 1) node[i] = node[i * 2].Mul(node[i * 2 + 1]);
    node[0] = *this;
    fi(1, _n * 2) node[i] = node[i / 2].DivMod(node[i]).second;
    vector<LL> y(_n);
    fi(0, _n) y[i] = node[_n + i][0];
    return y;
  }
  Poly Interpolate(const vector<LL> &x, const vector<LL> &y) const {
    const int _n = x.size();
  }
};
#undef fi
#undef Fi
template<int MAXN, LL P, LL RT> NTT<MAXN, P, RT> Poly<MAXN, P, RT>::ntt;
template<int MAXN, LL P, LL RT> const LL Poly<MAXN, P, RT>::INV2 = ntt.minv(2);
using Poly_t = Poly<131072 * 2, 998244353, 3>;