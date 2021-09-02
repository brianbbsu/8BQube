int z[MAXN];
int Manacher(string tmp) {
  string s = "&";
  int l = 0, r = 0, x, ans;
  for (char c : tmp) s.pb(c), s.pb('%');
  ans = 0, x = 0;
  for (int i = 1; i < SZ(s); ++i) {
    z[i] = r > i ? min(z[2 * l - i], r - i) : 1;
    while (s[i + z[i]] == s[i - z[i]]) ++z[i];
    if (z[i] + i > r) r = z[i] + i, l = i;
  }
  for (int i = 1; i < SZ(s); ++i)
    if (s[i] == '%') x = max(x, z[i]);
  ans = x / 2 * 2, x = 0;
  for (int i = 1; i < SZ(s); ++i)
    if (s[i] != '%') x = max(x, z[i]);
  return max(ans, (x - 1) / 2 * 2 + 1);
}
