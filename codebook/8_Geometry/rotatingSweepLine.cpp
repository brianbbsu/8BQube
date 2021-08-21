void rotatingSweepLine(vector<pii> &ps) {
  int n = SZ(ps);
  vector<int> id(n), pos(n);
  vector<pii> line(n * (n - 1) / 2);
  int m = 0;
  for (int i = 0; i < n; ++i)
    for (int j = i + 1; j < n; ++j)
      line[m++] = pii(i,j); 
    sort(ALL(line), [&](const pii &a, const pii &b)->bool {
      if (ps[a.X].X == ps[a.Y].X)
        return 0;
      if (ps[b.X].X == ps[b.Y].X)
        return 1;
      return (double)(ps[a.X].Y - ps[a.Y].Y) / (ps[a.X].X - ps[a.Y].X) < (double)(ps[b.X].Y - ps[b.Y].Y) / (ps[b.X].X - ps[b.Y].X);
  });
  iota(id, id + n, 0);
  sort(ALL(id), [&](const int &a,const int &b){ return ps[a] < ps[b]; });
  for (int i = 0; i < n; ++i) pos[id[i]] = i;
    for (int i = 0; i < m; ++i) {
      auto l = line[i];
      // meow
      tie(pos[l.X], pos[l.Y], id[pos[l.X]], id[pos[l.Y]]) = make_tuple(pos[l.Y], pos[l.X], l.Y, l.X);
  }
}
