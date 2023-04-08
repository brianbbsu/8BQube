pll area_pair(Line a, Line b) 
{ return pll(cross(a.Y - a.X, b.X - a.X), cross(a.Y - a.X, b.Y - a.X)); }
bool isin(Line l0, Line l1, Line l2) {
  // Check inter(l1, l2) strictly in l0
  auto [a123, a124] = area_pair(l0, l1);
  if (a123 - a124 < 0) swap(a123, a124), swap(l1.X, l1.Y);
  auto [b123, b124] = area_pair(l0, l2);
  if (b123 - b124 < 0) swap(l2.X, l2.Y);
  auto [c123, c124] = area_pair(l2, l1);
  if (c123 - c124 < 0) c123 *= -1, c124 *= -1;
  return c123 * (a123 - a124) < a123 * (c123 - c124); // C^4
}
/* Having solution, check size > 2 */
/* --^-- Line.X --^-- Line.Y --^-- */
vector<Line> halfPlaneInter(vector<Line> arr) {
  sort(ALL(arr), [&](Line a, Line b) -> int {
    if (cmp(a.Y - a.X, b.Y - b.X, 0) != -1)
      return cmp(a.Y - a.X, b.Y - b.X, 0);
    return ori(a.X, a.Y, b.Y) < 0;
  });
  deque<Line> dq(1, arr[0]);
  for (auto p : arr) {
    if (cmp(dq.back().Y - dq.back().X, p.Y - p.X, 0) == -1)
      continue;
    while (SZ(dq) >= 2 && !isin(p, dq[SZ(dq) - 2], dq.back()))
      dq.pop_back();
    while (SZ(dq) >= 2 && !isin(p, dq[0], dq[1]))
      dq.pop_front();
    dq.pb(p);
  }
  while (SZ(dq) >= 3 && !isin(dq[0], dq[SZ(dq) - 2], dq.back()))
    dq.pop_back();
  while (SZ(dq) >= 3 && !isin(dq.back(), dq[0], dq[1]))
    dq.pop_front();
  return vector<Line>(ALL(dq));
}
