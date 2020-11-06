void hull(vector<pll> &dots) {
  sort(dots.begin(), dots.end());
  vector<pll> ans(1, dots[0]);
  for (int ct = 0; ct < 2; ++ct, reverse(ALL(dots)))
    for (int i = 1, t = SZ(ans); i < SZ(dots); ans.pb(dots[i++]))
      while (SZ(ans) > t && ori(ans[SZ(ans) - 2], ans.back(), dots[i]) <= 0) 
        ans.pop_back();
  ans.pop_back(), ans.swap(dots);
}
