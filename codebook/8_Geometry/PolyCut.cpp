vector<pdd> cut(vector<pdd> poly, pdd s, pdd e) {
  vector<pdd> res;
  for (int i = 0; i < SZ(poly); ++i) {
    pdd cur = poly[i], prv = i ? poly[i - 1] : poly.back();
    bool side = ori(s, e, cur) < 0;
    if (side != (ori(s, e, prv) < 0))
      res.pb(intersect(s, e, cur, prv));
    if (side)
      res.pb(cur);
  }
  return res;
}
