#define fi(s, n) for (int i = (int)(s); i < (int)(n); ++i)
#define BIN_F(NAME, ARG1, BODY) auto NAME(ARG1) { return [=](cref x) BODY; }
#define UN_F(NAME, BODY) auto NAME(cref x) BODY
#define $ %
#define $$ ,
namespace PolyContext {
    using val = vector<LL>; // coefficients in [0, P)
    using ref = val&;
    using rref = val&&;
    using cref = const val&;
    constexpr int MAXN = 262144; // MAXN = 2^k
    constexpr LL P = 998244353, RT = 3;
    template<class F> auto operator $(cref x, F f) { return f(x); }
    NTT<MAXN, P, RT> ntt_provider;
    int n(cref x) { return (int)x.size(); } // n(x) >= 1
    UN_F(rev, {
        val z(x); reverse(z.data(), z.data() + n(z)); return z;
    })
    BIN_F(sz, int _n, { val z(x); z.resize(_n); return z; })
    BIN_F(ntt, bool f=0, { val z(x); ntt_provider(z.data(), n(z), f); return z; })
    BIN_F(cmul, LL k, { val z(x); fi(0, n(z)) z[i] = z[i] * k % P; return z; })
    BIN_F(vadd, cref y, { val z(x); fi(0, n(z)) if ((z[i] += y[i]) >= P) z[i] -= P; return z; })
    BIN_F(clone, int _n, {
        val z(_n);
        copy_n(x.data(), min(n(x), _n), z.data());
        return z;
    })
    BIN_F(mul, cref y, {
        int _n = 1;
        while (_n < n(x) + n(y) - 1) _n <<= 1;
        val a = x $ clone(_n) $ ntt();
        val b = y $ clone(_n) $ ntt();
        fi(0, _n) a[i] = a[i] * b[i] % P;
        return a $ ntt(1) $ sz(n(x) + n(y) - 1);
    })
    UN_F(inv, -> val {  // x[0] != 0
        if (n(x) == 1) return {ntt_provider.minv(x[0])};
        int _n = 1;
        while (_n < n(x) * 2) _n <<= 1;
        val xi = x $ clone((n(x) + 1) / 2) $ inv $ sz(_n) $ ntt();
        val a = x $ clone(_n) $ ntt();
        fi(0, _n) {
            xi[i] *= (2 - xi[i] * a[i]) % P;
            if ((xi[i] %= P) < 0) xi[i] += P;
        }
        return xi $ ntt(1) $ sz(n(x));
    })
    UN_F(sqrt, -> val { // Jacobi(x[0], P) == 1, P != 2
        if (n(x) == 1) return {QuadraticResidue(x[0], P)};
        val a = x $ clone((n(x) + 1) / 2) $ sqrt $ sz(n(x));
        return a $ inv $ mul(x) $ sz(n(x)) $ vadd(a) $ cmul(P / 2 + 1);
    })
    BIN_F(divmod, cref y, -> pair<val $$ val> { // y[-1] != 0
        if (n(x) < n(y)) return {{0} $$ x};
        int _n = n(x) - n(y) + 1;
        val a = y $ rev $ sz(_n);
        val b = x $ rev $ sz(_n);
        val q = a $ inv $ mul(b) $ sz(_n) $ rev;
        a = q $ mul(y); b = x;
        fi(0, n(x)) if ((b[i] -= a[i]) < 0) b[i] += P;
        return {q $$ b $ sz(max(1, n(y) - 1))};
    })
}
#undef fi
namespace ctx1 = PolyContext;
