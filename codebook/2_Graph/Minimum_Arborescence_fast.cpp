/* TODO
DSU: disjoint set
- DSU(n), .boss(x), .Union(x, y)
min_heap<T, Info>: min heap for type {T, Info} with lazy tag
- .push({w, i}), .top(), .join(heap), .pop(), .empty(), .add_lazy(v)
*/
struct E { int s, t; ll w; }; // 0-base
vector<int> dmst(const vector<E> &e, int n, int root) {
  vector<min_heap<ll, int>> h(n * 2);
  for (int i = 0; i < SZ(e); ++i)
    h[e[i].t].push({e[i].w, i});
  DSU dsu(n * 2);
  vector<int> v(n * 2, -1), pa(n * 2, -1), r(n * 2);
  v[root] = n + 1;
  int pc = n;
  for (int i = 0; i < n; ++i) if (v[i] == -1) {
    for (int p = i; v[p] == -1 || v[p] == i; p = dsu.boss(e[r[p]].s)) {
      if (v[p] == i) {
        int q = p; p = pc++;
        do {
          h[q].add_lazy(-h[q].top().X);
          pa[q] = p, dsu.Union(p, q), h[p].join(h[q]);
        } while ((q = dsu.boss(e[r[q]].s)) != p);
      }
      v[p] = i;
      while (!h[p].empty() && dsu.boss(e[h[p].top().Y].s) == p)
        h[p].pop();
      if (h[p].empty()) return {}; // no solution
      r[p] = h[p].top().Y;
    }
  }
  vector<int> ans;
  for (int i = pc - 1; i >= 0; i--) if (i != root && v[i] != n) {
    for (int f = e[r[i]].t; ~f && v[f] != n; f = pa[f])
      v[f] = n;
    ans.pb(r[i]);
  }
  return ans;
} // O(Ef(E)), f(E) from min_heap
