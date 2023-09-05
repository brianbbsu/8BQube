struct convex_hull_3D {
struct Face {
  int a, b, c;
  Face(int ta, int tb, int tc): a(ta), b(tb), c(tc) {}
}; // return the faces with pt indexes
vector<Face> res;
vector<Point> P;
convex_hull_3D(const vector<Point> &_P): res(), P(_P) {
// all points coplanar case will WA, O(n^2)
  int n = SZ(P);
  if (n <= 2) return; // be careful about edge case
  // ensure first 4 points are not coplanar
  swap(P[1], *find_if(ALL(P), [&](auto p) { return sign(abs2(P[0] - p)) != 0; }));
  swap(P[2], *find_if(ALL(P), [&](auto p) { return sign(abs2(cross3(p, P[0], P[1]))) != 0; }));
  swap(P[3], *find_if(ALL(P), [&](auto p) { return sign(volume(P[0], P[1], P[2], p)) != 0; }));
  vector<vector<int>> flag(n, vector<int>(n));
  res.emplace_back(0, 1, 2); res.emplace_back(2, 1, 0);
  for (int i = 3; i < n; ++i) {
    vector<Face> next;
    for (auto f : res) {
      int d = sign(volume(P[f.a], P[f.b], P[f.c], P[i]));
      if (d <= 0) next.pb(f);
      int ff = (d > 0) - (d < 0);
      flag[f.a][f.b] = flag[f.b][f.c] = flag[f.c][f.a] = ff;
    }
    for (auto f : res) {
      auto F = [&](int x, int y) {
        if (flag[x][y] > 0 && flag[y][x] <= 0)
          next.emplace_back(x, y, i);
      };
      F(f.a, f.b); F(f.b, f.c); F(f.c, f.a);
    }
    res = next;
  }
}
bool same(Face s, Face t) {
  if (sign(volume(P[s.a], P[s.b], P[s.c], P[t.a])) != 0) return 0;
  if (sign(volume(P[s.a], P[s.b], P[s.c], P[t.b])) != 0) return 0;
  if (sign(volume(P[s.a], P[s.b], P[s.c], P[t.c])) != 0) return 0;
  return 1;
}
int polygon_face_num() {
  int ans = 0;
  for (int i = 0; i < SZ(res); ++i)
    ans += none_of(res.begin(), res.begin() + i, [&](Face g) { return same(res[i], g); });
  return ans;
}
double get_volume() {
  double ans = 0;
  for (auto f : res)
    ans += volume(Point(0, 0, 0), P[f.a], P[f.b], P[f.c]);
  return fabs(ans / 6);
}
double get_dis(Point p, Face f) {
  Point p1 = P[f.a], p2 = P[f.b], p3 = P[f.c];                    
  double a = (p2.y - p1.y) * (p3.z - p1.z) - (p2.z - p1.z) * (p3.y - p1.y); 
  double b = (p2.z - p1.z) * (p3.x - p1.x) - (p2.x - p1.x) * (p3.z - p1.z); 
  double c = (p2.x - p1.x) * (p3.y - p1.y) - (p2.y - p1.y) * (p3.x - p1.x); 
  double d = 0 - (a * p1.x + b * p1.y + c * p1.z); 
  return fabs(a * p.x + b * p.y + c * p.z + d) / sqrt(a * a + b * b + c * c);                    
}
};
