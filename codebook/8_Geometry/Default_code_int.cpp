typedef pair<double, double> pdd;
typedef pair<pll, pll> Line;
pll operator+(pll a, pll b)
{ return pll(a.X + b.X, a.Y + b.Y); }
pll operator-(pll a, pll b)
{ return pll(a.X - b.X, a.Y - b.Y); }
pll operator*(pll a, ll b)
{ return pll(a.X * b, a.Y * b); }
pll operator/(pll a, ll b)
{ return pll(a.X / b, a.Y / b); }
pdd operator/(pll a, double b)
{ return pdd(a.X / b, a.Y / b); }
ll dot(pll a, pll b)
{ return a.X * b.X + a.Y * b.Y; }
ll cross(pll a, pll b)
{ return a.X * b.Y - a.Y * b.X; }
ll abs2(pll a)
{ return dot(a, a); }
int sign(ll a)
{ return a == 0 ? 0 : a > 0 ? 1 : -1; }
int ori(pll a, pll b, pll c)
{ return sign(cross(b - a, c - a)); }
bool collinearity(pll p1, pll p2, pll p3)
{ return sign(cross(p1 - p3, p2 - p3)) == 0; }
bool btw(pll p1, pll p2, pll p3) {
  if (!collinearity(p1, p2, p3)) return 0;
  return sign(dot(p1 - p3, p2 - p3)) <= 0;
}
bool seg_intersect(pll p1, pll p2, pll p3, pll p4) {
  int a123 = ori(p1, p2, p3);
  int a124 = ori(p1, p2, p4);
  int a341 = ori(p3, p4, p1);
  int a342 = ori(p3, p4, p2);
  if (a123 == 0 && a124 == 0)
    return btw(p1, p2, p3) || btw(p1, p2, p4) ||
      btw(p3, p4, p1) || btw(p3, p4, p2);
  return a123 * a124 <= 0 && a341 * a342 <= 0;
}
pdd intersect(pll p1, pll p2, pll p3, pll p4) {
  ll a123 = cross(p2 - p1, p3 - p1);
  ll a124 = cross(p2 - p1, p4 - p1);
  return (p4 * a123 - p3 * a124) / double(a123 - a124); // C^3 / C^2
}
pll perp(pll p1)
{ return pll(-p1.Y, p1.X); }
