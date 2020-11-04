struct Clique_Cover { // 0-base, O(n2^n)
    int dp[1 << N], n;
    int G[1 << N], G2[N], S[(1 << N) + 1];
    int parity[1 << N];
    void init(int _n) {
        n = _n, fill_n(dp, 1 << n, 0);
        fill_n(G2, n, 0), fill_n(S, 1 << n, 0);
    }
    void add_edge(int u, int v) {
        G2[u] |= 1 << v, G2[v] |= 1 << u;
    }
    int solve() {
        vector<pii> v;
        for (int i = 0; i < n; ++i)
            G2[i] |= 1 << i, G[1 << i] = G2[i];
        dp[0] = 1, G[0] = (1 << n) - 1;
        parity[0] = (n & 1) * 2 - 1;
        for (int i = 1; i < (1 << n); ++i) {
            int t = i & -i;
            parity[i] = -parity[i ^ t];
            if (dp[i ^ t]) {
                G[i] = G[i ^ t] & G[t];
                if ((G[i] & i) == i) dp[i] = 1;
            }
        }
        fwt(dp, 1 << n);
        for (int i = 0; i < (1 << n); ++i)
            S[dp[i]] += parity[i];
        for (int i = 0; i < (1 << n); ++i)
            if (S[i]) v.pb(pii(i, S[i]));
        for (int ans = 1; ans < n; ++ans) {
            int sum = 0;
            for (auto &p : v) sum += (p.second *= p.first);
            if (sum) return ans;
        }
        return n;
    }
};
