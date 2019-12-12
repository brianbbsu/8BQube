/* Delaunay Triangulation:
   Given a sets of points on 2D plane, find a
   triangulation such that no points will strictly
   inside circumcircle of any triangle.
find : return a triangle contain given point
add_point : add a point into triangulation
A Triangle is in triangulation iff. its has_chd is 0.
Region of triangle u: iterate each u.edge[i].tri,
each points are u.p[(i+1)%3], u.p[(i+2)%3]
calculation involves O(|V|^6) */
const double inf = 1e9;
double eps = 1e-6;  // 0 when integer
// return p4 is in circumcircle of tri(p1,p2,p3)
bool in_cc(P &p1, P &p2, P &p3, P &p4) {
  int o1 = (abs(p1.x) >= inf * 0.99 || abs(p1.y) >= inf * 0.99);
  int o2 = (abs(p2.x) >= inf * 0.99 || abs(p2.y) >= inf * 0.99);
  int o3 = (abs(p3.x) >= inf * 0.99 || abs(p3.y) >= inf * 0.99);
  int rtrue = o1 + o2 + o3; 
  int rfalse = abs(p4.x) >= inf * 0.99 || abs(p4.y) >= inf * 0.99;
  if (rtrue == 3) return true;
  if (rtrue) {
    P in(0, 0), out(0, 0);
    if (o1) out = out + p1; else in = in + p1;
    if (o2) out = out + p2; else in = in + p2;
    if (o3) out = out + p3; else in = in + p3;
    return (p4 - in) * (out - in) > 0;
  }
  if (rfalse) return false;
  // ^ ?
  double u11 = p1.x - p4.x, u12 = p1.y - p4.y;
  double u21 = p2.x - p4.x, u22 = p2.y - p4.y;
  double u31 = p3.x - p4.x, u32 = p3.y - p4.y;
  double u13 = sq(p1.x) - sq(p4.x) + sq(p1.y) - sq(p4.y);
  double u23 = sq(p2.x) - sq(p4.x) + sq(p2.y) - sq(p4.y);
  double u33 = sq(p3.x) - sq(p4.x) + sq(p3.y) - sq(p4.y);
  double det = -u13 * u22 * u31 + u12 * u23 * u31 + u13 * u21 * u32 - u11 * u23 * u32 - u12 * u21 * u33 + u11 * u22 * u33;
  return det > eps;
}
double side(P &a, P &b, P &p) { return (b - a) ^ (p - a); }
struct Tri;
struct Edge {
  Tri *tri;
  int side;
  Edge() : tri(0), side(0) {}
  Edge(Tri *_tri, int _side) : tri(_tri), side(_side) {}
};
struct Tri {
  P p[3];
  Edge edge[3];
  Tri *ch[3];
  Tri() {}
  Tri(P p0, P p1, P p2) {
    p[0] = p0; p[1] = p1; p[2] = p2;
    ch[0] = ch[1] = ch[2] = 0;
  }
  bool has_ch() { return ch[0] != 0; }
  int num_ch() {
    return ch[0] == 0 ? 0 : ch[1] == 0 ? 1 : ch[2] == 0 ? 2 : 3;
  }
  bool contains(P &q) {
    for (int i = 0; i < 3; ++i)
      if (side(p[i], p[(i + 1) % 3], q) < -eps) return false;
    return true;
  }
} pool[maxn * 10], *tris;
void edge(Edge a, Edge b) {
  if (a.tri) a.tri->edge[a.side] = b;
  if (b.tri) b.tri->edge[b.side] = a;
}
struct Trig { 
  Trig() {
    the_root = new (tris++) Tri(P(-inf, -inf), P(inf * 2, -inf), P(-inf, inf * 2));
  }  // all p should in
  Tri *find(P p) { return find(the_root, p); }
  void add_point(P &p) { add_point(find(the_root, p), p); }
  Tri *the_root;
  static Tri *find(Tri *root, P &p) {
    while (true) {
      if (!root->has_ch()) return root;
      for (int i = 0; i < 3 && root->ch[i]; ++i)
        if (root->ch[i]->contains(p)) {
          root = root->ch[i];
          break;
        }
    }
    assert(false);  // "point not found"
  }
  void add_point(Tri *root, P &p) {
    Tri *tab, *tbc, *tca;
    tab = new (tris++) Tri(root->p[0], root->p[1], p);
    tbc = new (tris++) Tri(root->p[1], root->p[2], p);
    tca = new (tris++) Tri(root->p[2], root->p[0], p);
    edge(Edge(tab, 0), Edge(tbc, 1));
    edge(Edge(tbc, 0), Edge(tca, 1));
    edge(Edge(tca, 0), Edge(tab, 1));
    edge(Edge(tab, 2), root->edge[2]);
    edge(Edge(tbc, 2), root->edge[0]);
    edge(Edge(tca, 2), root->edge[1]);
    root->ch[0] = tab; root->ch[1] = tbc; root->ch[2] = tca;
    flip(tab, 2); flip(tbc, 2); flip(tca, 2);
  }
  void flip(Tri *tri, int pi) {
    Tri *trj = tri->edge[pi].tri;
    int pj = tri->edge[pi].side;
    if (!trj) return;
    if (!in_cc(tri->p[0], tri->p[1], tri->p[2], trj->p[pj])) return;
    /* flip edge between tri,trj */
    Tri *trk = new (tris++) Tri(tri->p[(pi + 1) % 3], trj->p[pj], tri->p[pi]);
    Tri *trl = new (tris++) Tri(trj->p[(pj + 1) % 3], tri->p[pi], trj->p[pj]);
    edge(Edge(trk, 0), Edge(trl, 0));
    edge(Edge(trk, 1), tri->edge[(pi + 2) % 3]);
    edge(Edge(trk, 2), trj->edge[(pj + 1) % 3]);
    edge(Edge(trl, 1), trj->edge[(pj + 2) % 3]);
    edge(Edge(trl, 2), tri->edge[(pi + 1) % 3]);
    tri->ch[0] = trk; tri->ch[1] = trl; tri->ch[2] = 0;
    trj->ch[0] = trk; trj->ch[1] = trl; trj->ch[2] = 0;
    flip(trk, 1); flip(trk, 2);
    flip(trl, 1); flip(trl, 2);
  }
};
vector<Tri *> triang;
set<Tri *> vst;
void go(Tri *now) {
  if (vst.find(now) != vst.end()) return;
  vst.insert(now);
  if (!now->has_ch()) {
    triang.push_back(now);
    return;
  }
  for (int i = 0; i < now->num_ch(); ++i) go(now->ch[i]);
}
void build(int n, P *ps) { 
  tris = pool;
  random_shuffle(ps, ps + n);
  Trig tri;
  for (int i = 0; i < n; ++i) tri.add_point(ps[i]);
  go(tri.the_root);
}
