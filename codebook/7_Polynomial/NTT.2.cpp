#include <bits/stdc++.h>
using namespace std;
using ll = long long;
constexpr int MAXN = 1 << 20;
template<int MOD, int RT>
struct Zp {
    #define OP(op) static int op(int x, int y)
    OP(add) { return (x += y) >= MOD ? x - MOD : x; }
    OP(sub) { return (x -= y) < 0 ? x + MOD : x; }
    OP(mul) { return int(ll(x) * y % MOD); }
    static int mpow(int a, int n) {
        int r = 1;
        while (n) {
            if (n % 2) r = mul(r, a);
            n /= 2, a = mul(a, a);
        }
        return r;
    }
    static int minv(int a) { return mpow(a, MOD - 2); }
    struct NTT; struct Poly;
    static NTT ntt;
};
template<int MOD, int RT>
struct Zp<MOD, RT>::NTT {
    int w[MAXN];
    NTT() {
        int s = MAXN / 2, dw = mpow(RT, (MOD - 1) / MAXN);
        for (; s; s >>= 1, dw = mul(dw, dw)) {
            w[s] = 1;
            for (int j = 1; j < s; ++j) 
                w[s + j] = mul(w[s + j - 1], dw);
        }
    }
    void apply(int *a, int n, bool inv = 0) { //0 <= a_i < P
        for (int i = 0, j = 1; j < n - 1; ++j) {
            for (int k = n >> 1; (i ^= k) < k; k >>= 1);
            if (j < i) swap(a[i], a[j]);
        }
        for (int s = 1; s < n; s <<= 1) {
            for (int i = 0; i < n; i += s * 2) {
                for (int j = 0; j < s; ++j) {
                    int tmp = mul(a[i + s + j], w[s + j]);
                    a[i + s + j] = sub(a[i + j], tmp);
                    a[i + j] = add(a[i + j], tmp);
                }
            }
        }
        if (!inv) return;
        int iv = minv(n); reverse(a + 1, a + n);
        for (int i = 0; i < n; ++i) a[i] = mul(a[i], iv);
    }
};
template<int MOD, int RT>
typename Zp<MOD, RT>::NTT Zp<MOD, RT>::ntt;
using ctx1 = Zp<998244353, 3>;
int a[MAXN];
int main() {
    ios::sync_with_stdio(false);
    cin.tie(nullptr);
    for (int i = 0; i < 10; ++i) {
        a[i] = rand() % 100;
        cout << a[i] << " \n"[i == 9];
    }
    ctx1::ntt.apply(a, MAXN);
    for (int i = 0; i < 10; ++i) {
        cout << a[i] << " \n"[i == 9];
    }
    ctx1::ntt.apply(a, MAXN, 1);
    for (int i = 0; i < 10; ++i) {
        cout << a[i] << " \n"[i == 9];
    }
    return 0;
}
