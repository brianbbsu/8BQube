bool isin( Line l0, Line l1, Line l2 ) {
  // Check inter(l1, l2) in l0
  pdd p = intersect(l1.X, l1.Y, l2.X, l2.Y);
  return sign(cross(l0.Y - l0.X,p - l0.X)) > 0;
}
/* Having solution, check intersect(ret[0], ret[1])
 * in all the lines. (use (l.Y - l.X) ^ (p - l.X) > 0
 */
/* --^-- Line.X --^-- Line.Y --^-- */
vector<Line> halfPlaneInter(vector<Line> lines) {
  vector<double> ata(SZ(lines)), ord(SZ(lines));
  for(int i = 0; i < SZ(lines); ++i) {
    ord[i] = i;
    pdd d = lines[i].Y - lines[i].X;
    ata[i] = atan2(d.Y, d.X);
  }
  sort(ALL(ord), [&](int i, int j) {
    if (fabs(ata[i] - ata[j]) >= eps)
      return ata[i] < ata[j];
    return ori(lines[i].X, lines[i].Y, lines[j].Y) < 0; 
  });
  vector<Line> fin(1, lines[ord[0]]);
  for (int i = 1; i < SZ(lines); ++i)
    if (fabs(ata[ord[i]] - ata[ord[i - 1]]) > eps)
      fin.pb(lines[ord[i]]);
  deque<Line> dq;
  for (int i = 0; i < SZ(fin); ++i) {
    while (SZ(dq) >= 2 && !isin(fin[i], dq[SZ(dq) - 2], dq.back())) 
      dq.pop_back();
    while (SZ(dq) >= 2 && !isin(fin[i], dq[0], dq[1]))
      dq.pop_front();
    dq.pb(fin[i]);
  }
  while (SZ(dq) >= 3 && !isin(dq[0], dq[SZ(dq) - 2], dq.back()))
    dq.pop_back();
  while (SZ(dq) >= 3 && !isin(dq.back(), dq[0], dq[1])) 
    dq.pop_front();
  return vector<Line>(ALL(dq));
}
