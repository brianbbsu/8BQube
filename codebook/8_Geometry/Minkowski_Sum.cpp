vector<pll> Minkowski(vector<pll> A, vector<pll> B) {
  hull(A), hull(B);
  vector<pll> C(1, A[0] + B[0]), s1, s2; 
  for(int i = 0; i < SZ(A); ++i) 
    s1.pb(A[(i + 1) % SZ(A)] - A[i]);
  for(int i = 0; i < SZ(B); i++) 
    s2.pb(B[(i + 1) % SZ(B)] - B[i]);
  for(int p1 = 0, p2 = 0; p1 < SZ(A) || p2 < SZ(B);)
    if (p2 >= SZ(B) || (p1 < SZ(A) && cross(s1[p1], s2[p2]) >= 0))
      C.pb(C.back() + s1[p1++]);
    else
      C.pb(C.back() + s2[p2++]);
  return hull(C), C;
}
