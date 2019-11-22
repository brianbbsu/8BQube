int prc[maxn];
long long phic[msz][nsz];

void sieve() {
    bitset<maxn> v;
    pr.push_back(0);
    for (int i = 2; i < maxn; ++i) {
        if (!v[i]) pr.push_back(i);
        for (int j = 1; i * pr[j] < maxn; ++j) {
            v[i * pr[j]] = true;
            if (i % pr[j] == 0) break;
        }
    }
    for (int i = 1; i < pr.size(); ++i) prc[pr[i]] = 1;
    for (int i = 1; i < maxn; ++i) prc[i] += prc[i - 1];
}
long long p2(long long, long long);
long long phi(long long m, long long n) {
    if (m < msz && n < nsz && phic[m][n] != -1) return phic[m][n];
    if (n == 0) return m;
    if (pr[n] >= m) return 1;
    long long ret = phi(m, n - 1) - phi(m / pr[n], n - 1);
    if (m < msz && n < nsz) phic[m][n] = ret;
    return ret;
}
long long pi(long long m) {
    if (m < maxn) return prc[m];
    long long n = pi(cbrt(m));
    return phi(m, n) + n - 1 - p2(m, n);
}
long long p2(long long m, long long n) {
    long long ret = 0;
    long long lim = sqrt(m);
    for (int i = n + 1; pr[i] <= lim; ++i) ret += pi(m / pr[i]) - pi(pr[i]) + 1;
    return ret;
}
