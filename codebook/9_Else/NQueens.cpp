void solve(vector<int> &ret, int n) { // no sol when n=2,3
  if (n % 6 == 2) {
    for (int i = 2; i <= n; i += 2) ret.push_back(i);
    ret.push_back(3); ret.push_back(1);
    for (int i = 7; i <= n; i += 2) ret.push_back(i);
    ret.push_back(5);
  } else if (n % 6 == 3) {
    for (int i = 4; i <= n; i += 2) ret.push_back(i);
    ret.push_back(2);
    for (int i = 5; i <= n; i += 2) ret.push_back(i);
    ret.push_back(1); ret.push_back(3);
  } else {
    for (int i = 2; i <= n; i += 2) ret.push_back(i);
    for (int i = 1; i <= n; i += 2) ret.push_back(i);
  }
}
