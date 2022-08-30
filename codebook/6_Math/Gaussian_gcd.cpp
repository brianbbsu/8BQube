cpx gaussian_gcd(cpx a, cpx b) {
#define rnd(a, b) ((a >= 0 ? a * 2 + b : a * 2 - b) / (b * 2))
  ll c = a.real() * b.real() + a.imag() * b.imag();
  ll d = a.imag() * b.real() - a.real() * b.imag();
  ll r = b.real() * b.real() + b.imag() * b.imag();
  if (c % r == 0 && d % r == 0) return b;
  return gaussian_gcd(b, a - cpx(rnd(c, r), rnd(d, r)) * b);
}
