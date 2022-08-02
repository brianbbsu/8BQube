void solve(Point *a, int n) {
    sort(a, a + n, [](const Point &p, const Point &q) {
        return p.x + p.y < q.x + q.y;
    });
    set<Point> st; // greater<Point::x>
    for (int i = 0; i < n; ++i) {
        for (auto it = st.lower_bound(a[i]); it != st.end(); it = st.erase(it)) {
            if (it -> x - it -> y < a[i].x - a[i].y) break;
            es.push_back({it -> u, a[i].u, dist(*it, a[i])});
        }
        st.insert(a[i]);
    }
}
void MST(Point *a, int n) {
    for (int t = 0; t < 2; ++t) {
        solve(a, n);
        for (int i = 0; i < n; ++i) swap(a[i].x, a[i].y);
        solve(a, n);
        for (int i = 0; i < n; ++i) a[i].x = -a[i].x;
    }
}
