double ConvexHullDist(vector<pdd> A, vector<pdd> B) {
    for (auto &p : B) p = {-p.X, -p.Y};
    auto C = Minkowski(A, B);
    if (PointInConvex(C, pdd(0, 0))) return 0;
    double ans = 1e9;
    for (int i = 0; i < SZ(C); ++i) {
        ans = min(ans, dot(C[i], C[i]));
        const int j = i + 1 == SZ(C) ? 0 : i + 1;
        auto p = foot(C[i], C[j], pdd(0, 0));
        if (!btw(C[i], C[j], p)) continue;
        ans = min(ans, dot(p, p));
    }
    return sqrt(ans);
}
