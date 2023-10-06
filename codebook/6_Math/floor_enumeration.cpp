// enumerating x = floor(n / i), [l, r]
for (int l = 1, r; l <= n; l = r + 1) {
  int x = n / l;
  r = n / x;
}
