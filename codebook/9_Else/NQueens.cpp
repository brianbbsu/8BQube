void solve(vector<int> &ret, int n) { // no sol when n=2,3
  if (n % 6 == 2) {
    for (int i = 2; i <= n; i += 2) ret.pb(i);
    ret.pb(3); ret.pb(1);
    for (int i = 7; i <= n; i += 2) ret.pb(i);
    ret.pb(5);
  } else if (n % 6 == 3) {
    for (int i = 4; i <= n; i += 2) ret.pb(i);
    ret.pb(2);
    for (int i = 5; i <= n; i += 2) ret.pb(i);
    ret.pb(1); ret.pb(3);
  } else {
    for (int i = 2; i <= n; i += 2) ret.pb(i);
    for (int i = 1; i <= n; i += 2) ret.pb(i);
  }
}
