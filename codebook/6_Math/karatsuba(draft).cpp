struct karatsuba {
#define ADD(x, y) if ((x += y) >= MOD) x -= MOD;
#define SUB(x, y) if ((x -= y) < 0) x += MOD;
    int mem[MAXN * 4];
    void mul(const int *x, const int *y, int n, int *ebp, int *esp) {
        ebp = esp, esp += 2 * n;
        if (n <= 8) {
            fill(ebp, esp, 0);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < n; ++j) {
                    ebp[i + j] = (ebp[i + j] + (ll)x[i] * y[j]) % MOD;
                }
            }
            return;
        }
        int *q0 = ebp, *q1 = ebp + n / 2, *q2 = ebp + n, *q3 = ebp + n / 2 * 3;
        copy_n(x + n / 2, n / 2, q2);
        copy_n(y + n / 2, n / 2, q3);
        for (int i = 0; i < n / 2; ++i) ADD(q2[i], x[i]);
        for (int i = 0; i < n / 2; ++i) ADD(q3[i], y[i]);
        mul(q2, q3, n / 2, ebp, esp);
        copy_n(esp, n, q1);

        mul(x, y, n / 2, ebp, esp);
        copy_n(esp, n / 2, q0);
        for (int i = n / 2; i < n; ++i) ADD(q0[i], esp[i]);
        for (int i = 0; i < n; ++i) SUB(q1[i], esp[i]);
        mul(x + n / 2, y + n / 2, n / 2, ebp, esp);
        copy_n(esp + n / 2, n / 2, q3);
        for (int i = 0; i < n / 2; ++i) ADD(q2[i], esp[i]); 
        for (int i = 0; i < n; ++i) SUB(q1[i], esp[i]); 
    }
    void mul(int *x, int n, int *y, int m) {
        int L = 2 << __lg(max({n, m, 2}) - 1);
        fill(x + n, x + L, 0), fill(y + m, y + L, 0);
        mul(x, y, L, mem, mem);
    }
};

