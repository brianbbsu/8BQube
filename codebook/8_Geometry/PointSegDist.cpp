double PointSegDist(pdd q0, pdd q1, pdd p) {
    pdd ft = foot(q0, q1, p);
    if (btw(q0, q1, ft)) return abs(p - ft);
    return min(abs(p - q0), abs(p - q1));
}
