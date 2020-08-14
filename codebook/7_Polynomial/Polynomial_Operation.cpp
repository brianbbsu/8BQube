template<int MAXN, LL P, LL RT> //MAXN must be 2^k
struct PolyOp {
    NTT<MAXN, P, RT> ntt;
    const LL INV2 = ntt.minv(2);
    int get_sz(int n) {
        int sz = 1;
        while (sz < n) sz <<= 1;
        return sz;
    }
    void mul(LL *a, int n, LL *b, int m, LL *c) {
        static LL buf1[MAXN], buf2[MAXN];
        int sz = get_sz(n + m - 1);
        copy(a, a + n, buf1), fill(buf1 + n, buf1 + sz, 0);
        copy(b, b + m, buf2), fill(buf2 + m, buf2 + sz, 0);
        ntt(buf1, sz), ntt(buf2, sz);
        for (int i = 0; i < sz; ++i) c[i] = buf1[i] * buf2[i] % P;
        ntt(c, sz, true);
    }
    void inv(LL *a, int n, LL *b) {
        static LL buf[MAXN];
        if (n == 1) return b[0] = ntt.minv(a[0]), void();
        inv(a, (n + 1) / 2, b);
        int sz = get_sz(n * 2);
        copy(a, a + n, buf), fill(buf + n, buf + sz, 0);
        fill(b + n, b + sz, 0);
        ntt(buf, sz), ntt(b, sz);
        for (int i = 0; i < sz; ++i) {
            b[i] *= (2 - b[i] * buf[i]) % P;
            if ((b[i] %= P) < 0) b[i] += P;
        }
        ntt(b, sz, true), fill(b + n, b + sz, 0);
    }
    LL _msqrt(LL x) {
        for (LL i = 0; i <= P / 2; ++i) if (i * i % P == x) return i;
        throw string("BBQube");
    }
    void sqrt(LL *a, int n, LL *b) {
        static LL invb[MAXN], buf[MAXN];
        if (n == 1) return b[0] = _msqrt(a[0]), void();
        sqrt(a, (n + 1) / 2, b);
        int sz = get_sz(n * 2);
        inv(b, n, invb);
        copy(a, a + n, buf), fill(buf + n, buf + sz, 0);
        ntt(b, sz), ntt(invb, sz), ntt(buf, sz);
        for (int i = 0; i < sz; ++i) {
            if ((b[i] += buf[i] * invb[i] % P) >= P) b[i] -= P;
            b[i] = b[i] * INV2 % P;
        }
        ntt(b, sz, true), fill(b + n, b + sz, 0);
    }
    void div(LL *a, int n, LL *b, int m, LL *q, LL *r) {
        static LL invb[MAXN], buf[MAXN];
        if (n < m) {
            fill(q, q + m, 0), copy(a, a + n, r), fill(r + n, r + m, 0);
            return;
        }
        int mod_sz = n - m + 1;
        copy(b, b + m, buf), reverse(buf, buf + m);
        if (m < mod_sz) fill(buf + m, buf + mod_sz, 0);
        inv(buf, mod_sz, invb);
        copy(a, a + n, buf), reverse(buf, buf + n);
        mul(buf, mod_sz, invb, mod_sz, q);
        fill(q + mod_sz, q + n, 0), reverse(q, q + mod_sz);
        mul(b, m, q, mod_sz, buf);
        for (int i = 0; i < n; ++i) {
            if ((r[i] = a[i] - buf[i]) < 0) r[i] += P;
        }
    }
};
