double ConvexHullDist(vector<pdd> A, vector<pdd> B) {
    for (auto &p : B) p = {-p.X, -p.Y};
    auto C = Minkowski(A, B); // assert SZ(C) > 0
    if (PointInConvex(C, pdd(0, 0))) return 0;
    double ans = PointSegDist(C.back(), C[0], pdd(0, 0));
    for (int i = 0; i + 1 < SZ(C); ++i) {
        ans = min(ans, PointSegDist(C[i], C[i + 1], pdd(0, 0)));
    }
    return ans;
}
