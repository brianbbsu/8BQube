/* Delaunay Triangulation:
Given a sets of points on 2D plane, find a
triangulation such that no points will strictly
inside circumcircle of any triangle. */
struct Edge {
  int id; // oidx[id]
  list<Edge>::iterator twin;
  Edge(int _id = 0):id(_id) {}
};
struct Delaunay { // 0-base
  int n, oidx[N];
  list<Edge> head[N]; // result udir. graph
  pll p[N];
  void init(int _n, pll _p[]) {
    n = _n, iota(oidx, oidx + n, 0);
    for (int i = 0; i < n; ++i) head[i].clear();
    sort(oidx, oidx + n, [&](int a, int b) 
    { return _p[a] < _p[b]; });
    for (int i = 0; i < n; ++i) p[i] = _p[oidx[i]];
    divide(0, n - 1);
  }
  void addEdge(int u, int v) {
    head[u].push_front(Edge(v));
    head[v].push_front(Edge(u));
    head[u].begin()->twin = head[v].begin();
    head[v].begin()->twin = head[u].begin();
  }
  void divide(int l, int r) {
    if (l == r) return;
    if (l + 1 == r) return addEdge(l, l + 1);
    int mid = (l + r) >> 1;
    divide(l, mid), divide(mid + 1, r);
    int nowl = l, nowr = r;
    for (int update = 1; update;) {
      update = 0;
      pll ptL = p[nowl], ptR = p[nowr];
      for (auto it : head[nowl]) {
        pll t = p[it.id];
        int v = ori(ptR, ptL, t);
        if (v > 0 || (v == 0 && abs2(ptR - t) < abs2(ptR - ptL))) {
          nowl = it.id, update = 1;
          break;
        }
      }
      if (update)	continue;
      for (auto it : head[nowr]) {
        pll t = p[it.id];
        int v = ori(ptL, ptR, t);
        if (v < 0 || (v == 0 && abs2(ptL - t) < abs2(ptL - ptR))) {
          nowr = it.id, update = 1;
          break;
        }
      }
    }
    addEdge(nowl, nowr); // add tangent
    while (true) {
      pll ptL = p[nowl], ptR = p[nowr];
      int ch = -1, side = 0;
      for (auto it : head[nowl])
        if (ori(ptL, ptR, p[it.id]) > 0 && (ch == -1 || in_cc({ptL, ptR, p[ch]}, p[it.id])))
          ch = it.id, side = -1;
      for (auto it : head[nowr])
        if (ori(ptR, p[it.id], ptL) > 0 && (ch == -1 || in_cc({ptL, ptR, p[ch]}, p[it.id])))
          ch = it.id, side = 1;
      if (ch == -1) break; // upper common tangent
      if (side == -1) {
        for (auto it = head[nowl].begin(); it != head[nowl].end(); )
          if (seg_strict_intersect(ptL, p[it->id], ptR, p[ch]))
            head[it->id].erase(it->twin), head[nowl].erase(it++);
          else ++it;
        nowl = ch, addEdge(nowl, nowr);
      } 
      else {
        for (auto it = head[nowr].begin(); it != head[nowr].end(); )
          if (seg_strict_intersect(ptR, p[it->id], ptL, p[ch]))
            head[it->id].erase(it->twin), head[nowr].erase(it++);
          else ++it;
        nowr = ch, addEdge(nowl, nowr);
      }
    }
  }
} tool;
