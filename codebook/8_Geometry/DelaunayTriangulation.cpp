struct pddi {
    pdd p;
    int id;
    pddi(double a = 0, double b = 0, int c = -1):p(pdd(a, b)), id(c) {}
};
struct Edge {
    int id;
    list<Edge>::iterator twin;
    Edge(int _id = 0):id(_id) {}
};
int inCircle(pddi a, pddi b, pddi c, pddi p) {
    if (ori(a.p, b.p, c.p) < 0)
        swap(b, c);
    Point a3(a.p), b3(b.p), c3(c.p), p3(p.p);
    b3 = b3 - a3, c3 = c3 - a3, p3 = p3 - a3;
    Point f = cross(b3, c3); // normal vector
    return sign(dot(p3, f)); // check same direction, in: < 0, on: = 0, out: > 0
}
int intersection(pddi a, pddi b, pddi c, pddi d) { // seg(a, b) and seg(c, d)
    return ori(a.p, c.p, b.p) * ori(a.p, b.p, d.p) > 0 && ori(c.p, a.p, d.p) * ori(c.p, d.p, b.p) > 0;
}
struct Delaunay { // 0-base
    list<Edge> head[N]; // graph
    pddi p[N];
    int n, rename[N];
    void init(int _n, pddi _p[]) {
        n = _n;
        for (int i = 0; i < n; ++i) head[i].clear();
        for (int i = 0; i < n; ++i) p[i] = _p[i];
        sort(p, p + n, [&](pddi a, pddi b){return a.p < b.p;});
        for (int i = 0; i < n; ++i) rename[p[i].id] = i;
        divide(0, n - 1);
    }
    void addEdge(int u, int v) {
        head[u].push_front(Edge(v));
        head[v].push_front(Edge(u));
        head[u].begin() -> twin = head[v].begin();
        head[v].begin() -> twin = head[u].begin();
    }
    void divide(int l, int r) {
        if (l == r) return;
        if (l + 1 == r) return addEdge(l, l + 1);
        int mid = (l + r) >> 1;
        divide(l, mid), divide(mid + 1, r);
        int nowl = l, nowr = r;
        for (int update = 1; update;) {
            update = 0;
            pddi ptL = p[nowl], ptR = p[nowr];
            for (auto it : head[nowl]) {
                pddi t = p[it.id];
                int v = ori(ptR.p, ptL.p, t.p);
                if (v > 0 || (v == 0 && abs2(ptR.p - t.p) < abs2(ptR.p - ptL.p))) {
                    nowl = it.id, update = 1;
                    break;
                }
            }
            if (update)	continue;
            for (auto it : head[nowr]) {
                pddi t = p[it.id];
                int v = ori(ptL.p, ptR.p, t.p);
                if (v < 0 || (v == 0 && abs2(ptL.p - t.p) < abs2(ptL.p - ptR.p))) {
                    nowr = it.id, update = 1;
                    break;
                }
            }
        }
        addEdge(nowl, nowr); // add tangent
        while (true) {
            pddi ptL = p[nowl], ptR = p[nowr];
            int ch = -1, side = 0;
            for (auto it : head[nowl])
                if (ori(ptL.p, ptR.p, p[it.id].p) > 0 && (ch == -1 || inCircle(ptL, ptR, p[ch], p[it.id]) < 0))
                    ch = it.id, side = -1;
            for (auto it : head[nowr])
                if (ori(ptR.p, p[it.id].p, ptL.p) > 0 && (ch == -1 || inCircle(ptL, ptR, p[ch], p[it.id]) < 0))
                    ch = it.id, side = 1;
            if (ch == -1) break; // upper common tangent
            if (side == -1) {
                for (auto it = head[nowl].begin(); it != head[nowl].end(); )
                    if (intersection(ptL, p[it -> id], ptR, p[ch]))
                        head[it -> id].erase(it -> twin), head[nowl].erase(it++);
                    else ++it;
                nowl = ch, addEdge(nowl, nowr);
            } 
            else {
                for (auto it = head[nowr].begin(); it != head[nowr].end(); )
                    if (intersection(ptR, p[it -> id], ptL, p[ch]))
                        head[it -> id].erase(it -> twin), head[nowr].erase(it++);
                    else ++it;
                nowr = ch, addEdge(nowl, nowr);
            }
        }
    }
    vector<pii> getEdge() {
        vector<pii> ret;
        for (int i = 0; i < n; ++i)
            for (auto it : head[i])
                if (it.id >= i)
                    ret.pb(pii(p[i].id, p[it.id].id));
        return ret;
    }
} tool;
