struct Matrix {
  int n, m;
  ll M[MAXN][MAXN];
  int row_swap(int i, int j) {
    if (i == j) return 0;
    for (int k = 0; k < m; ++k)
      swap(M[i][k], M[j][k]);
    return 1;
  }
  ll det() { // return the number of swaps
    int rt = 0;
    for (int i = 0; i < n; ++i) {
      int piv = i;
      while (piv < n && !M[piv][i]) ++piv;
      if (piv == n) continue;
      rt += row_swap(i, piv);
      for (int j = i + 1; j < n; ++j) {
        while (M[j][i]) {
          int tmp = P - M[i][i] / M[j][i];
          for (int k = i; k < m; ++k)
            M[i][k] = (M[j][k] * tmp + M[i][k]) % P;
          rt += row_swap(i, j);
        }
      }
    }
    rt = (rt & 1) ? P - 1 : 1;
    for (int i = 0; i < n; ++i)
      rt = rt * M[i][i] % P;
    return rt; 
    // round(rt) if using double to cal. int. det
  }
};
