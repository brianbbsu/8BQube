template<size_t S> // sum(a) < S
bitset<S> SubsetSum(const int *a, int n) {
    vector<int> c(S);
    bitset<S> dp; dp[0] = 1;
    for (int i = 0; i < n; ++i) ++c[a[i]];
    for (size_t i = 1; i < S; ++i) {
        while (c[i] > 2) c[i] -= 2, ++c[i * 2];
        while (c[i]--) dp |= dp << i;
    }
    return dp;
}
