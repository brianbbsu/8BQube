using i128 = __int128;
struct LN {
  ll a, b, c; // ax + by + c <= 0
  pll dir() const { return pll(a, b); }
  LN(ll ta, ll tb, ll tc) : a(ta), b(tb), c(tc) {}
  LN(pll S, pll T): a((T-S).Y), b(-(T-S).X), c(cross(T,S)) {}
};
pdd intersect(LN A, LN B) {
  double c = cross(A.dir(), B.dir());
  i128 a = i128(A.c) * B.a - i128(B.c) * A.a;
  i128 b = i128(A.c) * B.b - i128(B.c) * A.b;
  return pdd(-b / c, a / c);
}
bool cov(LN l, LN A, LN B) {
  i128 c = cross(A.dir(), B.dir());
  i128 a = i128(A.c) * B.a - i128(B.c) * A.a;
  i128 b = i128(A.c) * B.b - i128(B.c) * A.b;
  return sign(a * l.b - b * l.a + c * l.c) * sign(c) >= 0;
}
bool operator<(LN a, LN b) {
  if (int c = cmp(a.dir(), b.dir(), false); c != -1) return c;
  return i128(abs(b.a) + abs(b.b)) * a.c > i128(abs(a.a) + abs(a.b)) * b.c;
}
